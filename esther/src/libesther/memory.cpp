#include "esther/memory.h"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <queue>
#include <vector>

//#define VERBOSE_GC

struct Registers {
    ptr_t reg[5];
};

#ifdef __x86_64
asm("saveRegisters:\n"
    "mov %rbx,0x0(%rdi)\n"
    "mov %r12,0x8(%rdi)\n"
    "mov %r13,0x10(%rdi)\n"
    "mov %r14,0x18(%rdi)\n"
    "mov %r15,0x20(%rdi)\n"
    "xor %rax,%rax\n"
    "ret");
#elif __i386
asm("_saveRegisters:\n"
    "mov 0x4(%esp),%eax\n"
    "mov %ebx,0x0(%eax)\n"
    "mov %ecx,0x4(%eax)\n"
    "mov %edx,0x8(%eax)\n"
    "mov %edi,0xc(%eax)\n"
    "mov %esi,0x10(%eax)\n"
    "xor %eax,%eax\n"
    "ret");
#endif

extern "C" void saveRegisters(Registers *buf);

static const size_t InitialHeapSize = 20000;
static const double HeapSizeMultiplier = 1.8;

class ObjectHeader {
    uint32_t flags;
    size_t size;

public:
    enum {
        FlagMark = 1 << 0,
        FlagFree = 1 << 1
    };

    ObjectHeader(size_t size, uint32_t flags = 0);

    bool hasFlag(int flag) const;
    void setFlag(int flag);
    void removeFlag(int flag);

    size_t getSize() const;
    void setSize(size_t size);
};

inline bool ObjectHeader::hasFlag(int flag) const {
    return flags & flag;
}

inline void ObjectHeader::setFlag(int flag) {
    flags |= flag;
}

inline void ObjectHeader::removeFlag(int flag) {
    flags &= ~flag;
}

inline size_t ObjectHeader::getSize() const {
    return size;
}

inline void ObjectHeader::setSize(size_t size) {
    this->size = size;
}

ObjectHeader::ObjectHeader(size_t size, uint32_t flags)
    : flags(flags)
    , size(size) {
}

struct FreeObject {
    ObjectHeader *header;
    size_t heapIndex;
};

struct CompareObjects {
    bool operator()(const FreeObject &a, const FreeObject &b);
};

bool CompareObjects::operator()(const FreeObject &a, const FreeObject &b) {
    return a.header->getSize() < b.header->getSize();
}

static void Mapper_virtual_mapOnReferences(Mapper *, MapFunction) {
}

void Mapper_init(Mapper *self) {
    self->mapOnReferences = Mapper_virtual_mapOnReferences;
}

void Mapper_mapOnReferences(Mapper *self, MapFunction f) {
    self->mapOnReferences(self, f);
}

static void ManagedObject_virtual_finalize(ManagedObject *) {
}

void ManagedObject_init(ManagedObject *self) {
    Mapper_init(&self->base);

    self->finalize = ManagedObject_virtual_finalize;
}

void ManagedObject_finalize(ManagedObject *self) {
    self->finalize(self);
}

typedef std::priority_queue<FreeObject, std::vector<FreeObject>, CompareObjects> FreeObjectQueue;

static std::vector<uint8_t *> heaps;
static std::vector<uint32_t> heapSizes;
static std::vector<uint8_t *> bitmaps;

static uint8_t *heapMin, *heapMax;

static size_t objectCount, memoryUsed;

static FreeObjectQueue freeObjects;

static ptr_ptr_t stackBottom, stackTop;

static std::vector<Mapper *> mappers;

static bool enoughSpace(size_t size) {
    return !freeObjects.empty() && freeObjects.top().header->getSize() >= size;
}

static void mark(ManagedObject *object);

static void markReference(ManagedObject **ref) {
    if (*ref != nullptr && !(reinterpret_cast<ObjectHeader *>(*ref) - 1)->hasFlag(ObjectHeader::FlagMark))
        mark(*ref);
}

static void mark(ManagedObject *object) {
    (reinterpret_cast<ObjectHeader *>(object) - 1)->setFlag(ObjectHeader::FlagMark);
    Mapper_mapOnReferences((Mapper *)object, markReference);
}

static inline size_t bitmapSize(size_t size) {
    return size % (sizeof(void *) * 8) ? size / (sizeof(void *) * 8) + 1 : size / (sizeof(void *) * 8);
}

static inline size_t bitmapByte(size_t i) {
    return i / (sizeof(void *) * 8);
}

static inline size_t bitmapBit(size_t i) {
    return (i / sizeof(void *)) % 8;
}

static inline void markAsAllocation(uint8_t *p, size_t heapIndex) {
    size_t headerByte = p - heaps[heapIndex];
    bitmaps[heapIndex][bitmapByte(headerByte)] |= 1 << bitmapBit(headerByte);
}

static inline bool isAllocation(uint8_t *p, size_t heapIndex) {
    size_t headerByte = p - heaps[heapIndex];
    return bitmaps[heapIndex][bitmapByte(headerByte)] & (1 << bitmapBit(headerByte));
}

static void markFree(uint8_t *p, size_t size, size_t heapIndex) {
    freeObjects.push({ new (p) ObjectHeader(size, ObjectHeader::FlagFree), heapIndex });
    markAsAllocation(p, heapIndex);
}

static void sweep() {
    objectCount = 0;
    memoryUsed = 0;

    freeObjects = FreeObjectQueue();

    for (size_t i = 0; i < heaps.size(); i++) {
        memset(bitmaps[i], 0, bitmapSize(heapSizes[i]));

        ObjectHeader *header;

        for (uint8_t *p = heaps[i]; p < heaps[i] + heapSizes[i]; p += header->getSize()) {
            header = reinterpret_cast<ObjectHeader *>(p);

            if (header->hasFlag(ObjectHeader::FlagMark)) {
                header->removeFlag(ObjectHeader::FlagMark);

                objectCount++;
                memoryUsed += header->getSize();

                markAsAllocation(p, i);
            } else {
                ObjectHeader *freeHeader;
                size_t freeSize = 0;

                for (uint8_t *free = p; free < heaps[i] + heapSizes[i]; free += freeHeader->getSize()) {
                    freeHeader = reinterpret_cast<ObjectHeader *>(free);

                    if (freeHeader->hasFlag(ObjectHeader::FlagMark))
                        break;

                    if (!freeHeader->hasFlag(ObjectHeader::FlagFree) && freeHeader->getSize() > sizeof(ObjectHeader)) {
                        ManagedObject *object = reinterpret_cast<ManagedObject *>(freeHeader + 1);
                        ManagedObject_finalize(object);
                    }

                    freeSize += freeHeader->getSize();
                }

                markFree(p, freeSize, i);
            }
        }
    }
}

static bool isValidPtr(uint8_t *p) {
    if (reinterpret_cast<ptr_t>(p) % sizeof(void *) != 0)
        return false;

    if (p < heapMin + sizeof(ObjectHeader) || p >= heapMax)
        return false;

    size_t i;

    for (i = 0; i < heaps.size(); i++)
        if (p >= heaps[i] + sizeof(ObjectHeader) && p < heaps[i] + heapSizes[i])
            break;

    if (i == heaps.size())
        return false;

    ObjectHeader *header = reinterpret_cast<ObjectHeader *>(p) - 1;

    if (!isAllocation(reinterpret_cast<uint8_t *>(header), i))
        return false;

    if (header->hasFlag(ObjectHeader::FlagFree))
        return false;

    return true;
}

static void markRange(ptr_ptr_t p, size_t n) {
    for (size_t i = 0; i < n; i++, p++)
        if (isValidPtr(reinterpret_cast<uint8_t *>(*p)))
            mark(reinterpret_cast<ManagedObject *>(*p));
}

static void mark() {
    markRange(stackTop, stackBottom - stackTop);

    Registers buf;
    saveRegisters(&buf);

    markRange(reinterpret_cast<ptr_ptr_t>(&buf), sizeof(Registers) / sizeof(ptr_t));

    for (Mapper *mapper : mappers)
        Mapper_mapOnReferences(mapper, markReference);
}

static void addHeap() {
    size_t heapSize = heaps.empty() ? InitialHeapSize : heapSizes.back() * HeapSizeMultiplier;

#ifdef VERBOSE_GC
    IO::writeLine("ConservativeMemoryManager::addHeap() // size=%u\n", heapSize);
#endif

    heaps.push_back(static_cast<uint8_t *>(malloc(heapSize)));
    heapSizes.push_back(heapSize);
    bitmaps.push_back(static_cast<uint8_t *>(calloc(bitmapSize(heapSize), 1)));

    if (!heapMin || heaps.back() < heapMin)
        heapMin = heaps.back();

    if (!heapMax || heaps.back() + heapSize > heapMax)
        heapMax = heaps.back() + heapSize;

    markFree(heaps.back(), heapSize, heaps.size() - 1);
}

static ManagedObject *claimFreeSpace(size_t size) {
    ObjectHeader *header = freeObjects.top().header;
    size_t heapIndex = freeObjects.top().heapIndex;

    freeObjects.pop();

    if (header->getSize() >= size + sizeof(ObjectHeader)) {
        markFree(reinterpret_cast<uint8_t *>(header) + size, header->getSize() - size, heapIndex);
        header->setSize(size);
    }

    header->removeFlag(ObjectHeader::FlagFree);

    return reinterpret_cast<ManagedObject *>(header + 1);
}

void gc_initialize(ptr_ptr_t bp) {
    stackBottom = bp;

    heapMin = heapMax = nullptr;

    objectCount = 0;
    memoryUsed = 0;
}

void gc_finalize() {
#ifdef VERBOSE_GC
    size_t totalMemory = 0;

    for (uint32_t size : heapSizes)
        totalMemory += size + bitmapSize(size);

    IO::writeLine("\nObject count: %u", objectCount);
    IO::writeLine("Heaps used: %u", heaps.size());
    IO::writeLine("Memory used: %u", memoryUsed);
    IO::writeLine("Total memory: %u", totalMemory);
    IO::writeLine("\nConservativeMemoryManager::finalize()");
#endif

    ObjectHeader *header;

    for (size_t i = 0; i < heaps.size(); i++)
        for (uint8_t *p = heaps[i]; p < heaps[i] + heapSizes[i]; p += header->getSize()) {
            header = reinterpret_cast<ObjectHeader *>(p);

            if (!header->hasFlag(ObjectHeader::FlagFree) && header->getSize() > sizeof(ObjectHeader)) {
                ManagedObject *object = reinterpret_cast<ManagedObject *>(header + 1);
                ManagedObject_finalize(object);
            }
        }

    for (Mapper *mapper : mappers)
        free(mapper);
}

void gc_collect() {
#ifdef __x86_64
    register ptr_ptr_t sp asm("rsp");
#elif __i386
    register ptr_ptr_t sp asm("esp");
#endif

    stackTop = sp;

#ifdef VERBOSE_GC
    IO::writeLine("\nConservativeMemoryManager::collectGarbage()");
    size_t oldSize = man->memoryUsed, oldObjectCount = man->objectCount;
#endif

    mark();
    sweep();

#ifdef VERBOSE_GC
    IO::writeLine("//freed=%u, freedObjects=%u, objectCount=%u\n", oldSize - man->memoryUsed, oldObjectCount - man->objectCount, man->objectCount);
#endif
}

void *gc_alloc(size_t size) {
#ifdef VERBOSE_GC
    IO::writeLine("ConservativeMemoryManager::allocate(size=%u)", size);
#endif

    size += sizeof(ObjectHeader);

    if (!enoughSpace(size)) {
        if (!heaps.empty())
            gc_collect();

        if (!enoughSpace(size))
            addHeap();
    }

    objectCount++;
    memoryUsed += size;

    return claimFreeSpace(size);
}

void gc_free(void *) {
}

void gc_regiserMapper(Mapper *mapper) {
    mappers.push_back(mapper);
}

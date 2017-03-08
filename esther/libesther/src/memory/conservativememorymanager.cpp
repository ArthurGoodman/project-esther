#include "conservativememorymanager.h"

#include <cstring>
#include <memory>

#include "common/io.h"
#include "memory/managedobject.h"
#include "memory/objectheader.h"

#if defined(MEM_MANAGEMENT) && defined(CONSERVATIVE_GC)

namespace {

#ifdef __x86_64
struct Registers {
    uint64_t reg[5];
};

asm("saveRegisters:\n"
    "mov %rbx,0x0(%rdi)\n"
    "mov %r12,0x8(%rdi)\n"
    "mov %r13,0x10(%rdi)\n"
    "mov %r14,0x18(%rdi)\n"
    "mov %r15,0x20(%rdi)\n"
    "xor %rax,%rax\n"
    "ret");
#elif __i386
struct Registers {
    uint32_t reg[6];
};

asm("_saveRegisters:\n"
    "push %ebp\n"
    "mov %esp,%ebp\n"
    "mov 0x8(%ebp),%ebp\n"
    "mov %eax,0x0(%ebp)\n"
    "mov %ebx,0x4(%ebp)\n"
    "mov %ecx,0x8(%ebp)\n"
    "mov %edx,0xc(%ebp)\n"
    "mov %edi,0x10(%ebp)\n"
    "mov %esi,0x14(%ebp)\n"
    "pop %ebp\n"
    "xor %eax,%eax\n"
    "ret");
#endif

extern "C" void saveRegisters(Registers *buf);
}

namespace es {

const size_t ConservativeMemoryManager::InitialHeapSize = 20000;
const double ConservativeMemoryManager::HeapSizeMultiplier = 1.8;

ConservativeMemoryManager *ConservativeMemoryManager::man;

bool ConservativeMemoryManager::CompareObjects::operator()(const ConservativeMemoryManager::FreeObject &a, const ConservativeMemoryManager::FreeObject &b) {
    return a.header->getSize() < b.header->getSize();
}

ConservativeMemoryManager::ConservativeMemoryManager() {
    initialize();
}

ConservativeMemoryManager::~ConservativeMemoryManager() {
    finalize();
}

#ifdef __x86_64
void ConservativeMemoryManager::initStack(uint64_t *stackBottom) {
#elif __i386
void ConservativeMemoryManager::initStack(uint32_t *stackBottom) {
#endif
    man->stackBottom = stackBottom;
}

ManagedObject *ConservativeMemoryManager::allocate(size_t size, size_t count) {
#ifdef VERBOSE_GC
    IO::writeLine("ConservativeMemoryManager::allocate(size=%u)", size);
#endif

    size += sizeof(ObjectHeader);

    if (!man->enoughSpace(size)) {
        if (!man->heaps.empty())
            collectGarbage();

        if (!man->enoughSpace(size))
            man->addHeap();
    }

    man->objectCount += count;
    man->memoryUsed += size;

    return man->claimFreeSpace(size);
}

void ConservativeMemoryManager::free(ManagedObject *) {
}

void ConservativeMemoryManager::collectGarbage() {
#ifdef __x86_64
    register uint64_t *rsp asm("rsp");
    man->stackTop = rsp;
#elif __i386
    register uint32_t *esp asm("esp");
    man->stackTop = esp;
#endif

#ifdef VERBOSE_GC
    IO::writeLine("\nConservativeMemoryManager::collectGarbage()");
    size_t oldSize = man->memoryUsed, oldObjectCount = man->objectCount;
#endif

    man->mark();
    man->sweep();

#ifdef VERBOSE_GC
    IO::writeLine("//freed=%u, freedObjects=%u, objectCount=%u\n", oldSize - man->memoryUsed, oldObjectCount - man->objectCount, man->objectCount);
#endif
}

void ConservativeMemoryManager::registerMapper(Mapper *mapper) {
    man->mappers.push_back(mapper);
}

void ConservativeMemoryManager::initialize() {
    man = this;

    heapMin = heapMax = nullptr;

    objectCount = 0;
    memoryUsed = 0;
}

void ConservativeMemoryManager::finalize() {
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
                object->finalize();
            }
        }

    for (Mapper *mapper : mappers)
        delete mapper;
}

bool ConservativeMemoryManager::enoughSpace(size_t size) {
    return !freeObjects.empty() && freeObjects.top().header->getSize() >= size;
}

bool ConservativeMemoryManager::isValidPtr(uint8_t *p) {
#ifdef __x86_64
    if (reinterpret_cast<uint64_t>(p) % 8 != 0)
#elif __i386
    if (reinterpret_cast<uint32_t>(p) % 4 != 0)
#endif
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

void ConservativeMemoryManager::mark() {
    // IO::writeLine("Marking stack...");

    markRange(stackTop, stackBottom - stackTop);

    // IO::writeLine("Marking registers...");

    Registers buf;
    saveRegisters(&buf);

#ifdef __x86_64
    markRange(reinterpret_cast<uint64_t *>(&buf), sizeof(Registers) / sizeof(uint64_t));
#elif __i386
    markRange(reinterpret_cast<uint32_t *>(&buf), sizeof(Registers) / sizeof(uint32_t));
#endif

    // IO::writeLine("Marking globals...");

    for (Mapper *mapper : mappers)
        mapper->mapOnReferences(markReference);
}

#ifdef __x86_64
void ConservativeMemoryManager::markRange(uint64_t *p, size_t n) {
#elif __i386
void ConservativeMemoryManager::markRange(uint32_t *p, size_t n) {
#endif
    for (size_t i = 0; i < n; i++, p++)
        if (isValidPtr(reinterpret_cast<uint8_t *>(*p)))
            mark(reinterpret_cast<ManagedObject *>(*p));
}

void ConservativeMemoryManager::mark(ManagedObject *object) {
    // IO::writeLine("ptr: 0x%p", object);

    (reinterpret_cast<ObjectHeader *>(object) - 1)->setFlag(ObjectHeader::FlagMark);
    object->mapOnReferences(markReference);
}

void ConservativeMemoryManager::sweep() {
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
                        object->finalize();
                    }

                    freeSize += freeHeader->getSize();
                }

                markFree(p, freeSize, i);
            }
        }
    }
}

void ConservativeMemoryManager::addHeap() {
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

ManagedObject *ConservativeMemoryManager::claimFreeSpace(size_t size) {
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

void ConservativeMemoryManager::markFree(uint8_t *p, size_t size, size_t heapIndex) {
    freeObjects.push({ new (p) ObjectHeader(size, ObjectHeader::FlagFree), heapIndex });
    markAsAllocation(p, heapIndex);
}

void ConservativeMemoryManager::markReference(ManagedObject *&ref) {
    if (ref != nullptr && !(reinterpret_cast<ObjectHeader *>(ref) - 1)->hasFlag(ObjectHeader::FlagMark))
        man->mark(ref);
}
}

#endif

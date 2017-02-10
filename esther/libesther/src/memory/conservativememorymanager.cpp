#include "conservativememorymanager.h"

#include <memory>

#include "common/io.h"
#include "memory/objectheader.h"
#include "memory/managedobject.h"
#include "memory/ptr.h"

#if defined(MEM_MANAGEMENT) && defined(CONSERVATIVE_GC)

namespace {

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

void ConservativeMemoryManager::initStack(uint32_t *stackBottom) {
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
    uint8_t local;
    alloca(0);
    man->stackTop = reinterpret_cast<uint32_t *>(&local);

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

void ConservativeMemoryManager::reallocate() {
}

void ConservativeMemoryManager::initialize() {
    man = this;

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
}

bool ConservativeMemoryManager::enoughSpace(size_t size) {
    return !freeObjects.empty() && freeObjects.top().header->getSize() >= size;
}

int ConservativeMemoryManager::findHeap(void *p) {
    if (reinterpret_cast<uint32_t>(p) % 4 != 0)
        return -1;

    for (size_t i = 0; i < heaps.size(); i++)
        if (p >= heaps[i] + sizeof(ObjectHeader) && p < heaps[i] + heapSizes[i])
            return i;

    return -1;
}

void ConservativeMemoryManager::mark() {
    markRange(stackTop, stackBottom - stackTop);

    Registers buf;
    saveRegisters(&buf);

    markRange(reinterpret_cast<uint32_t *>(&buf), sizeof(Registers) / sizeof(uint32_t));

    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->ptr)
            mark(p->ptr);
}

void ConservativeMemoryManager::markRange(uint32_t *p, size_t n) {
    for (size_t i = 0; i < n; i++, p++) {
        int heapIndex = findHeap(reinterpret_cast<void *>(*p));

        if (heapIndex >= 0)
            mark(reinterpret_cast<ManagedObject *>(*p), heapIndex);
    }
}

void ConservativeMemoryManager::mark(ManagedObject *object, int heapIndex) {
    if (heapIndex < 0)
        heapIndex = findHeap(object);

    size_t headerByte = reinterpret_cast<uint8_t *>(object) - heaps[heapIndex] - sizeof(ObjectHeader);

    if (bitmaps[heapIndex][bitmapByte(headerByte)] & (1 << bitmapBit(headerByte))) {
        (reinterpret_cast<ObjectHeader *>(object) - 1)->setFlag(ObjectHeader::FlagMark);
        object->mapOnReferences(markReference);
    }
}

void ConservativeMemoryManager::sweep() {
    ObjectHeader *header;

    objectCount = 0;
    memoryUsed = 0;

    freeObjects = std::priority_queue<FreeObject, std::vector<FreeObject>, CompareObjects>();

    for (size_t i = 0; i < heaps.size(); i++) {
        for (uint8_t *p = heaps[i]; p < heaps[i] + heapSizes[i]; p += header->getSize()) {
            header = reinterpret_cast<ObjectHeader *>(p);

            if (header->hasFlag(ObjectHeader::FlagMark)) {
                header->removeFlag(ObjectHeader::FlagMark);

                objectCount++;
                memoryUsed += header->getSize();
            } else {
                ObjectHeader *freeHeader;
                size_t freeSize = 0;

                for (uint8_t *free = p; free < heaps[i] + heapSizes[i]; free += freeHeader->getSize()) {
                    freeHeader = reinterpret_cast<ObjectHeader *>(free);

                    if (freeHeader->hasFlag(ObjectHeader::FlagMark))
                        break;

                    if (!freeHeader->hasFlag(ObjectHeader::FlagFree) && freeHeader->getSize() > sizeof(ObjectHeader)) {
                        size_t headerByte = free - heaps[i];
                        bitmaps[i][bitmapByte(headerByte)] ^= 1 << bitmapBit(headerByte);

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

    bitmaps.push_back(static_cast<uint8_t *>(calloc(bitmapSize(heapSize), sizeof(uint8_t))));

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

    size_t headerByte = p - heaps[heapIndex];
    bitmaps[heapIndex][bitmapByte(headerByte)] |= 1 << bitmapBit(headerByte);
}

void ConservativeMemoryManager::markReference(ManagedObject *&ref) {
    if (!(reinterpret_cast<ObjectHeader *>(ref) - 1)->hasFlag(ObjectHeader::FlagMark))
        man->mark(ref);
}
}

#endif

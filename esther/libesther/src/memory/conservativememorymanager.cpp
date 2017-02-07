#include "conservativememorymanager.h"

#include <memory>

#include "common/io.h"
#include "common/bytearray.h"
#include "memory/managedobject.h"
#include "memory/freeobject.h"

#ifdef MEM_MANAGEMENT

namespace es {

const double ConservativeMemoryManager::HeapSizeMultiplier = 1.8;

ConservativeMemoryManager *ConservativeMemoryManager::man;

ConservativeMemoryManager::ConservativeMemoryManager() {
    initialize();
}

ConservativeMemoryManager::~ConservativeMemoryManager() {
    finalize();
}

ManagedObject *ConservativeMemoryManager::allocate(size_t size, size_t count) {
#ifdef VERBOSE_GC
    IO::writeLine("ConservativeMemoryManager::allocate(size=%u)", size);
#endif

    ManagedObject *newObject = man->findFreeSpace(size);

    if (newObject == nullptr)
        newObject = man->addHeap();

    man->claimFreeSpace(newObject, size);

    man->memoryUsed += size;
    man->objectCount += count;

    return newObject;
}

void ConservativeMemoryManager::free(ManagedObject *) {
}

void ConservativeMemoryManager::collectGarbage() {
#ifdef VERBOSE_GC
    IO::writeLine("\nConservativeMemoryManager::collectGarbage()");
    size_t oldSize = man->memoryUsed, oldObjectCount = man->objectCount;
#endif

#ifdef VERBOSE_GC
    IO::writeLine("//freed=%u, freedObjects=%u, objectCount=%u\n", oldSize - man->memoryUsed, oldObjectCount - man->objectCount, man->objectCount);
#endif
}

void ConservativeMemoryManager::reallocate() {
}

void ConservativeMemoryManager::initialize() {
    man = this;

    addHeap();

    objectCount = 0;
    memoryUsed = 0;
}

void ConservativeMemoryManager::finalize() {
#ifdef VERBOSE_GC
    size_t totalMemory = 0;

    for (ByteArray *heap : heaps)
        totalMemory += heap->getSize();

    IO::writeLine("\nObject count: %u", objectCount);
    IO::writeLine("Heaps used: %u", heaps.size());
    IO::writeLine("Memory used: %u", memoryUsed);
    IO::writeLine("Total memory: %u", totalMemory);
    IO::writeLine("\nConservativeMemoryManager::finalize()");
#endif
}

ManagedObject *ConservativeMemoryManager::findFreeSpace(size_t size) {
    ManagedObject *freeSpace = nullptr;

    for (ByteArray *heap : heaps) {
        size_t objectSize;

        for (uint8_t *p = heap->getData(); p <= heap->getData() + heap->getSize() - sizeof(ManagedObject); p += objectSize) {
            ManagedObject *object = reinterpret_cast<ManagedObject *>(p);
            objectSize = object->getSize();

            if (object->hasFlag(ManagedObject::FlagFree) && object->getSize() >= size) {
                freeSpace = object;
                break;
            }
        }

        if (freeSpace)
            break;
    }

    return freeSpace;
}

ManagedObject *ConservativeMemoryManager::addHeap() {
    size_t heapSize = heaps.empty() ? InitialHeapSize : heaps.back()->getSize() * HeapSizeMultiplier;

#ifdef VERBOSE_GC
    IO::writeLine("ConservativeMemoryManager::addHeap() // size=%u", heapSize);
#endif

    heaps.push_back(new ByteArray(heapSize));
    heaps.back()->allocate(heapSize);
    new (heaps.back()->getData()) FreeObject(heapSize);
    return reinterpret_cast<ManagedObject *>(heaps.back()->getData());
}

void ConservativeMemoryManager::claimFreeSpace(ManagedObject *freeSpace, size_t size) {
    if (freeSpace->getSize() >= size + sizeof(FreeObject))
        new (reinterpret_cast<uint8_t *>(freeSpace) + size) FreeObject(freeSpace->getSize() - size);
}
}

#endif

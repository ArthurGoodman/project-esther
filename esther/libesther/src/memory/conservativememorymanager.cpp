#include "conservativememorymanager.h"

#include <memory>

#include "common/io.h"
#include "common/bytearray.h"
#include "memory/objectheader.h"

#ifdef MEM_MANAGEMENT

namespace es {

const size_t ConservativeMemoryManager::InitialHeapSize = 1024;
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

    if (man->freeSpace == nullptr || man->freeSpace->getSize() < size + sizeof(ObjectHeader))
        man->addHeap();

    man->memoryUsed += size + sizeof(ObjectHeader);
    man->objectCount += count;

    return man->claimFreeSpace(size);
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

    objectCount = 0;
    memoryUsed = 0;
    freeSpace = nullptr;
}

void ConservativeMemoryManager::finalize() {
#ifdef VERBOSE_GC
    size_t totalMemory = 0;

    for (ByteArray *heap : heaps)
        totalMemory += heap->getCapacity();

    IO::writeLine("\nObject count: %u", objectCount);
    IO::writeLine("Heaps used: %u", heaps.size());
    IO::writeLine("Memory used: %u", memoryUsed);
    IO::writeLine("Total memory: %u", totalMemory);
    IO::writeLine("\nConservativeMemoryManager::finalize()");
#endif
}

//ManagedObject *ConservativeMemoryManager::findFreeSpace(size_t size) {
//    ManagedObject *freeSpace = nullptr;

//    for (ByteArray *heap : heaps) {
//        size_t objectSize;

//        for (uint8_t *p = heap->getData(); p <= heap->getData() + heap->getSize() - sizeof(ManagedObject); p += objectSize) {
//            ManagedObject *object = reinterpret_cast<ManagedObject *>(p);
//            objectSize = object->getSize();

//            if (object->hasFlag(ManagedObject::FlagFree) && object->getSize() >= size) {
//                freeSpace = object;
//                break;
//            }
//        }

//        if (freeSpace)
//            break;
//    }

//    return freeSpace;
//}

void ConservativeMemoryManager::addHeap() {
    size_t heapSize = heaps.empty() ? InitialHeapSize : heaps.back()->getSize() * HeapSizeMultiplier;

#ifdef VERBOSE_GC
    IO::writeLine("\nConservativeMemoryManager::addHeap() // size=%u\n", heapSize);
#endif

    heaps.push_back(new ByteArray(heapSize));
    heaps.back()->allocate(heapSize);

    freeSpace = new (heaps.back()->getData()) ObjectHeader(heapSize);
    freeSpace->setFlag(ObjectHeader::FlagFree);
}

ManagedObject *ConservativeMemoryManager::claimFreeSpace(size_t size) {
    ObjectHeader *object = freeSpace;

    if (freeSpace->getSize() >= size + 2 * sizeof(ObjectHeader)) {
        freeSpace = new (reinterpret_cast<uint8_t *>(freeSpace + 1) + size) ObjectHeader(freeSpace->getSize() - size - sizeof(ObjectHeader));
        freeSpace->setFlag(ObjectHeader::FlagFree);
    } else
        freeSpace = nullptr;

    object->setSize(size + sizeof(ObjectHeader));

    return reinterpret_cast<ManagedObject *>(object + 1);
}
}

#endif

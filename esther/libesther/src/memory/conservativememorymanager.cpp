#include "conservativememorymanager.h"

#include <memory>

#include "common/io.h"
#include "common/bytearray.h"
#include "memory/managedobject.h"

#ifdef MEM_MANAGEMENT

namespace es {

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

    ManagedObject *newObject = nullptr;

    for (ByteArray &heap : man->heaps)
        if (heap.enoughSpace(size)) {
            ManagedObject *object;
            size_t objectSize;

            for (uint8_t *p = heap.getData(); p < heap.getData() + HeapSize - sizeof(ManagedObject *); p += objectSize) {
                object = reinterpret_cast<ManagedObject *>(p);
                objectSize = object->getSize();

                if (object->hasFlag(ManagedObject::FlagFree) && object->getSize() >= size - sizeof(ManagedObject)) {
                    newObject = object;

                    ManagedObject *freeObject = new (reinterpret_cast<uint8_t *>(object) + size) ManagedObject;
                    freeObject->setFlag(ManagedObject::FlagFree);
                    freeObject->setForwardAddress(reinterpret_cast<ManagedObject *>(objectSize - size));
                }
            }
        }

    if (newObject == nullptr) {
        man->heaps.push_back(ByteArray(HeapSize));
        man->heaps.back().allocate(HeapSize);

        newObject = reinterpret_cast<ManagedObject *>(man->heaps.back().allocate(size));
    }

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

    heaps.push_back(ByteArray(HeapSize));
    heaps.back().allocate(HeapSize);

    objectCount = 0;
    memoryUsed = 0;
}

void ConservativeMemoryManager::finalize() {
#ifdef VERBOSE_GC
    IO::writeLine("\nObject count: %u", objectCount);
    IO::writeLine("Heaps used: %u", heaps.size());
    IO::writeLine("Memory used: %u", memoryUsed);
    IO::writeLine("Total memory: %u", heaps.size() * HeapSize);
    IO::writeLine("\nConservativeMemoryManager::finalize()");
#endif
}
}

#endif

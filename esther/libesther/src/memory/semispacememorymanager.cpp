#include "memory/semispacememorymanager.h"

#include <cstring>
#include <iostream>

#include "common/bytearray.h"
#include "common/io.h"
#include "memory/ptr.h"
#include "memory/managedobject.h"
#include "memory/memorymanager.h"

#ifdef MEM_MANAGEMENT

namespace {
es::ByteArray *memory;
size_t objectCount, memoryUsed, capacity;
int delta;
uint8_t *toSpace, *fromSpace, *allocPtr;
}

namespace es {

SemispaceMemoryManager::SemispaceMemoryManager() {
    initialize();
}

SemispaceMemoryManager::~SemispaceMemoryManager() {
    finalize();
}

ManagedObject *SemispaceMemoryManager::allocate(size_t size, size_t count) {
#ifdef VERBOSE_GC
    IO::writeLine("SemispaceMemoryManager::allocate(size=%u)", size);
#endif

    if (!enoughSpace(size))
        collectGarbage();

    if (!enoughSpace(size))
        expand();
    else
        delta = 0;

    ManagedObject *object = reinterpret_cast<ManagedObject *>(allocPtr);
    allocPtr += size;

    objectCount += count;
    memoryUsed += size;

    return object;
}

void SemispaceMemoryManager::free(ManagedObject *) {
}

void SemispaceMemoryManager::collectGarbage() {
#ifdef VERBOSE_GC
    IO::writeLine("\nSemispaceMemoryManager::collectGarbage()");
    size_t oldSize = memoryUsed;
#endif

    size_t oldObjectCount = objectCount;

    std::swap(fromSpace, toSpace);
    allocPtr = toSpace;

    objectCount = 0;
    memoryUsed = 0;

    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->ptr)
            updateReference(p->ptr);

    uint8_t *object = fromSpace;

    for (size_t i = 0, size = 0; i < oldObjectCount; i++, object += size) {
        size = reinterpret_cast<ManagedObject *>(object)->getSize();

        if (reinterpret_cast<ManagedObject *>(object)->getForwardAddress() == nullptr)
            reinterpret_cast<ManagedObject *>(object)->finalize();
    }

#ifdef VERBOSE_GC
    IO::writeLine("//freed=%u, freedObjects=%u, objectCount=%u\n", oldSize - memoryUsed, oldObjectCount - objectCount, objectCount);
#endif
}

void SemispaceMemoryManager::reallocate() {
}

void SemispaceMemoryManager::initialize() {
    memory = new ByteArray;

    objectCount = 0;
    memoryUsed = 0;
    capacity = InitialCapacity;
    delta = 0;

    toSpace = memory->allocate(capacity);
    fromSpace = toSpace + capacity / 2;
    allocPtr = toSpace;
}

void SemispaceMemoryManager::finalize() {
#ifdef VERBOSE_GC
    IO::writeLine("\nObject count: %u", objectCount);
    IO::writeLine("Memory used: %u", memoryUsed);
    IO::writeLine("Total memory: %u", memory->getCapacity());
    IO::writeLine("\nSemispaceMemoryManager::finalize()");
#endif

    uint8_t *object = toSpace;

    for (size_t i = 0, size = 0; i < objectCount; i++, object += size) {
        size = reinterpret_cast<ManagedObject *>(object)->getSize();
        reinterpret_cast<ManagedObject *>(object)->finalize();
    }

    delete memory;
}

bool SemispaceMemoryManager::enoughSpace(int size) {
    return allocPtr + size <= toSpace + capacity / 2;
}

ManagedObject *SemispaceMemoryManager::copy(ManagedObject *object) {
    if (object->getForwardAddress() == nullptr) {
        objectCount++;
        memoryUsed += object->getSize();

        ManagedObject *newObject = reinterpret_cast<ManagedObject *>(allocPtr);
        allocPtr += object->getSize();

        memcpy(newObject, object, object->getSize());

        object->setForwardAddress(newObject);

        newObject->mapOnReferences(updateReference);
    }

    return object->getForwardAddress();
}

void SemispaceMemoryManager::expand() {
#ifdef VERBOSE_GC
    IO::write("SemispaceMemoryManager::expand()");
#endif

    uint8_t *oldData = memory->getData();

    fromSpace = memory->allocate(capacity);
    toSpace = fromSpace - capacity;
    capacity *= 2;

    delta = memory->getData() - oldData;

#ifdef VERBOSE_GC
    IO::writeLine(" //capacity=%u, delta=%i", capacity, delta);
#endif

    collectGarbage();
}

void SemispaceMemoryManager::updateReference(ManagedObject *&ref) {
    ref = copy(reinterpret_cast<ManagedObject *>(reinterpret_cast<uint8_t *>(ref) + delta));
}
}

#endif

#include "semispacememorymanager.h"

#include <cstring>
#include <iostream>

#include "common/config.h"
#include "common/bytearray.h"
#include "memory/pointer.h"
#include "memory/managedobject.h"
#include "memory/memorymanager.h"

static ByteArray *memory;
static int objectCount, memoryUsed, capacity, delta;

static uint8_t *toSpace, *fromSpace, *allocPtr;

SemispaceMemoryManager::SemispaceMemoryManager() {
    initialize();
}

SemispaceMemoryManager::~SemispaceMemoryManager() {
    finalize();
}

ManagedObject *SemispaceMemoryManager::allocate(uint32_t size, int count) {
#if VERBOSE_GC
    std::cout << "SemispaceMemoryManager::allocate(size=" << size << ")\n" << std::flush;
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
#if VERBOSE_GC
    std::cout << "\nSemispaceMemoryManager::collectGarbage()\n" << std::flush;
    int oldSize = memoryUsed, oldObjectCount = objectCount;
#endif

    std::swap(fromSpace, toSpace);
    allocPtr = toSpace;

    objectCount = 0;
    memoryUsed = 0;

    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->pointer)
            p->pointer = copy(reinterpret_cast<ManagedObject *>(reinterpret_cast<uint8_t *>(p->pointer) + delta));

#if VERBOSE_GC
    std::cout << "//freed=" << oldSize - memoryUsed << " freedObjects=" << oldObjectCount - objectCount << ", objectCount=" << objectCount << "\n\n" << std::flush;
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
#if VERBOSE_GC
    std::cout << "\nObject count: " << objectCount << "\n" << std::flush;
    std::cout << "Memory used: " << memoryUsed << "\n" << std::flush;
    std::cout << "Total memory: " << memory->getCapacity() << "\n" << std::flush;
    std::cout << "\nSemispaceMemoryManager::finalize()\n" << std::flush;
#endif

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
#if VERBOSE_GC
    std::cout << "SemispaceMemoryManager::expand()" << std::flush;
#endif

    uint8_t *oldData = memory->getData();

    fromSpace = memory->allocate(capacity);
    toSpace = fromSpace - capacity;
    capacity *= 2;

    delta = memory->getData() - oldData;

#if VERBOSE_GC
    std::cout << " //capacity=" << capacity << ", delta=" << delta << "\n" << std::flush;
#endif

    collectGarbage();
}

void SemispaceMemoryManager::updateReference(ManagedObject *&ref) {
    ref = copy(reinterpret_cast<ManagedObject *>(reinterpret_cast<uint8_t *>(ref) + delta));
}

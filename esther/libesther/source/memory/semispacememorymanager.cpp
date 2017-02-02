#include "semispacememorymanager.h"

#include "pointer.h"
#include "managedobject.h"

#include <cstring>
#include <iostream>

SemispaceMemoryManager::SemispaceMemoryManager()
    : objectCount(0)
    , memoryUsed(0)
    , capacity(InitialCapacity)
    , delta(0) {
    initialize();
}

SemispaceMemoryManager::~SemispaceMemoryManager() {
    finalize();
}

ManagedObject *SemispaceMemoryManager::allocate(uint size, int count) {
#if VERBOSE_GC
    std::cout << "SemispaceMemoryManager::allocate(size=" << size << ")\n" << std::flush;
#endif

    if (!enoughSpace(size))
        collectGarbage();

    if (!enoughSpace(size))
        expand();
    else
        delta = 0;

    ManagedObject *object = (ManagedObject *)allocPtr;
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

    for (Ptr<ManagedObject>::Aux *p = pointers; p; p = p->next)
        if (p->pointer)
            p->pointer = copy((ManagedObject *)((byte *)p->pointer + delta));

// for (Frame *frame = frames(); frame; frame = frame->getNext())
//     frame->mapOnLocals([this](ManagedObject *&p) {
//         p = copy((ManagedObject *)((byte *)p + delta));
//     });

#if VERBOSE_GC
    std::cout << "//freed=" << oldSize - memoryUsed << " freedObjects=" << oldObjectCount - objectCount << ", objectCount=" << objectCount << "\n\n" << std::flush;
#endif
}

void SemispaceMemoryManager::reallocate() {
}

void SemispaceMemoryManager::initialize() {
    toSpace = memory.allocate(capacity);
    fromSpace = toSpace + capacity / 2;
    allocPtr = toSpace;
}

void SemispaceMemoryManager::finalize() {
#if VERBOSE_GC
    std::cout << "\nObject count: " << objectCount << "\n" << std::flush;
    std::cout << "Memory used: " << memoryUsed << "\n" << std::flush;
    std::cout << "Total memory: " << memory.getCapacity() << "\n" << std::flush;
    std::cout << "\nSemispaceMemoryManager::finalize()\n" << std::flush;
#endif
}

bool SemispaceMemoryManager::enoughSpace(int size) const {
    return allocPtr + size <= toSpace + capacity / 2;
}

ManagedObject *SemispaceMemoryManager::copy(ManagedObject *object) {
    if (object->getForwardAddress() == 0) {
        objectCount++;
        memoryUsed += object->getSize();

        ManagedObject *newObject = (ManagedObject *)allocPtr;
        allocPtr += object->getSize();

        memcpy(newObject, object, object->getSize());

        object->setForwardAddress(newObject);

        newObject->mapOnReferences([this](ManagedObject *&ref) {
            ref = copy((ManagedObject *)((byte *)ref + delta));
        });
    }

    return object->getForwardAddress();
}

void SemispaceMemoryManager::expand() {
#if VERBOSE_GC
    std::cout << "SemispaceMemoryManager::expand()" << std::flush;
#endif

    byte *oldData = memory.getData();

    fromSpace = memory.allocate(capacity);
    toSpace = fromSpace - capacity;
    capacity *= 2;

    delta = memory.getData() - oldData;

#if VERBOSE_GC
    std::cout << " //capacity=" << capacity << ", delta=" << delta << "\n" << std::flush;
#endif

    collectGarbage();
}

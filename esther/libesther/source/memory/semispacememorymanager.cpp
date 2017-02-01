#include "semispacememorymanager.h"

#include "pointer.h"
#include "managedobject.h"

#include <iostream>
#include <cstring>

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
    std::cout << "SemispaceMemoryManager::allocate()\n";

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
    std::cout << "\nSemispaceMemoryManager::collectGarbage()\n";

    int oldSize = memory.getSize();
    int oldObjectCount = objectCount;

    std::swap(fromSpace, toSpace);
    allocPtr = toSpace;

    objectCount = 0;
    memoryUsed = 0;

    for (Pointer<ManagedObject>::Aux *p = pointers; p; p = p->next)
        if (p->pointer)
            p->pointer = copy((ManagedObject *)((byte *)p->pointer + delta));

    // for (Frame *frame = frames(); frame; frame = frame->getNext())
    //     frame->mapOnLocals([this](ManagedObject *&p) {
    //         p = copy((ManagedObject *)((byte *)p + delta));
    //     });

    std::cout << "//freed=" << oldSize - memory.getSize() << ", freedObjects=" << oldObjectCount - objectCount << ", objectCount=" << objectCount << "\n\n";
}

void SemispaceMemoryManager::reallocate() {
}

void SemispaceMemoryManager::initialize() {
    toSpace = memory.allocate(capacity);
    fromSpace = toSpace + capacity / 2;
    allocPtr = toSpace;
}

void SemispaceMemoryManager::finalize() {
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

        // memcpy(newObject, object, object->getSize());
        object->copy((ManagedObject *)newObject);

        object->setForwardAddress(newObject);

        // newObject->mapOnReferences([this](ManagedObject *&ref) {
        //     ref = copy((ManagedObject *)((byte *)ref + delta));
        // });
    }

    return object->getForwardAddress();
}

void SemispaceMemoryManager::expand() {
    std::cout << "SemispaceMemoryManager::expand()";

    byte *oldData = memory.getData();

    fromSpace = memory.allocate(capacity);
    toSpace = fromSpace - capacity;
    capacity *= 2;

    delta = memory.getData() - oldData;

    std::cout << " // delta=" << delta << "\n";

    collectGarbage();
}

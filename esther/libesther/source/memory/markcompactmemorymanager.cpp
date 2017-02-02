#include "markcompactmemorymanager.h"

#include "managedobject.h"
#include "pointer.h"

#include <iostream>

MarkCompactMemoryManager::MarkCompactMemoryManager()
    : objectCount(0) {
    initialize();
}

MarkCompactMemoryManager::~MarkCompactMemoryManager() {
    finalize();
}

ManagedObject *MarkCompactMemoryManager::allocate(uint size, int count) {
#if VERBOSE_GC
    std::cout << "MarkCompactMemoryManager::allocate(size=" << size << ")\n" << std::flush;
#endif

    if (!memory.enoughSpace(size))
        collectGarbage();

    byte *oldData = memory.getData();

    ManagedObject *object = reinterpret_cast<ManagedObject *>(memory.allocate(size));

    if ((delta = memory.getData() - oldData) != 0)
        updatePointers();

    objectCount += count;

    return object;
}

void MarkCompactMemoryManager::free(ManagedObject *) {
}

void MarkCompactMemoryManager::collectGarbage() {
#if VERBOSE_GC
    std::cout << "\nMarkCompactMemoryManager::collectGarbage()\n" << std::flush;
    int oldSize = memory.getSize(), oldObjectCount = objectCount;
#endif

    mark();
    compact();

#if VERBOSE_GC
    std::cout << "//freed=" << oldSize - memory.getSize() << ", freedObjects=" << oldObjectCount - objectCount << ", objectCount=" << objectCount << "\n\n" << std::flush;
#endif
}

void MarkCompactMemoryManager::reallocate() {
    delta = memory.reallocate();
    updatePointers();
}

void MarkCompactMemoryManager::initialize() {
    ByteArray::setInitialCapacity(1024);
}

void MarkCompactMemoryManager::finalize() {
#if VERBOSE_GC
    std::cout << "\nObject count: " << objectCount << "\n" << std::flush;
    std::cout << "Memory used: " << memory.getSize() << "\n" << std::flush;
    std::cout << "Total memory: " << memory.getCapacity() << "\n" << std::flush;
    std::cout << "\nMarkCompactMemoryManager::finalize()\n" << std::flush;
#endif

    // byte *p = memory.getData();

    // for (int i = 0, size = 0; i < objectCount; i++, p += size) {
    //     size = ((ManagedObject *)p)->getSize();
    //     ((ManagedObject *)p)->~ManagedObject();
    // }
}

void MarkCompactMemoryManager::updatePointers() {
#if VERBOSE_GC
    std::cout << "MarkCompactMemoryManager::updatePointers() //delta=" << delta << "\n\n" << std::flush;
#endif

    byte *object = memory.getData();

    for (int i = 0; i < objectCount; i++, object += reinterpret_cast<ManagedObject *>(object)->getSize())
        updatePointers(reinterpret_cast<ManagedObject *>(object));

    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->pointer)
            updatePointer(p->pointer);
}

void MarkCompactMemoryManager::mark() {
    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->pointer && !p->pointer->hasFlag(ManagedObject::FlagMark))
            mark(p->pointer);
}

void MarkCompactMemoryManager::compact() {
    byte *object, *free;
    object = free = memory.getData();

    for (int i = 0; i < objectCount; i++, object += reinterpret_cast<ManagedObject *>(object)->getSize())
        if (reinterpret_cast<ManagedObject *>(object)->hasFlag(ManagedObject::FlagMark)) {
            reinterpret_cast<ManagedObject *>(object)->setForwardAddress(reinterpret_cast<ManagedObject *>(free));
            free += reinterpret_cast<ManagedObject *>(object)->getSize();
        }

    object = memory.getData();

    for (int i = 0; i < objectCount; i++, object += reinterpret_cast<ManagedObject *>(object)->getSize())
        if (reinterpret_cast<ManagedObject *>(object)->hasFlag(ManagedObject::FlagMark))
            forwardPointers(reinterpret_cast<ManagedObject *>(object));

    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->pointer && p->pointer->hasFlag(ManagedObject::FlagMark))
            p->pointer = p->pointer->getForwardAddress();

    object = memory.getData();

    int freeCount = 0, freeSize = 0;

    for (int i = 0, size = 0; i < objectCount; i++, object += size) {
        size = reinterpret_cast<ManagedObject *>(object)->getSize();

        if (reinterpret_cast<ManagedObject *>(object)->hasFlag(ManagedObject::FlagMark)) {
            byte *dst = reinterpret_cast<byte *>(reinterpret_cast<ManagedObject *>(object)->getForwardAddress());

            memmove(dst, object, size);

            reinterpret_cast<ManagedObject *>(dst)->removeFlag(ManagedObject::FlagMark);
            reinterpret_cast<ManagedObject *>(dst)->setForwardAddress(0);
        } else {
            freeSize += size;
            freeCount++;

            // ((ManagedObject *)object)->~ManagedObject();
        }
    }

    memory.free(freeSize);
    objectCount -= freeCount;
}

void MarkCompactMemoryManager::updatePointers(ManagedObject *object) {
    object->mapOnReferences([this](ManagedObject *&ref) {
        updatePointer(ref);
    });
}

void MarkCompactMemoryManager::forwardPointers(ManagedObject *object) {
    object->mapOnReferences([](ManagedObject *&ref) {
        ref = ref->getForwardAddress();
    });
}

void MarkCompactMemoryManager::mark(ManagedObject *object) {
    object->setFlag(ManagedObject::FlagMark);

    object->mapOnReferences([this](ManagedObject *&ref) {
        if (!ref->hasFlag(ManagedObject::FlagMark))
            mark(ref);
    });
}

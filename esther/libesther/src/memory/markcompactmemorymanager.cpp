#include "memory/markcompactmemorymanager.h"

#include <iostream>

#include "common/config.h"
#include "common/bytearray.h"
#include "common/io.h"
#include "memory/ptr.h"
#include "memory/managedobject.h"
#include "memory/memorymanager.h"

namespace {
es::ByteArray *memory;
size_t objectCount;
int delta;
}

namespace es {

MarkCompactMemoryManager::MarkCompactMemoryManager() {
    initialize();
}

MarkCompactMemoryManager::~MarkCompactMemoryManager() {
    finalize();
}

ManagedObject *MarkCompactMemoryManager::allocate(size_t size, size_t count) {
#if VERBOSE_GC
    IO::writeLine("MarkCompactMemoryManager::allocate(size=%u)", size);
#endif

    if (!memory->enoughSpace(size))
        collectGarbage();

    uint8_t *oldData = memory->getData();

    ManagedObject *object = reinterpret_cast<ManagedObject *>(memory->allocate(size));

    if ((delta = memory->getData() - oldData) != 0)
        updatePointers();

    objectCount += count;

    return object;
}

void MarkCompactMemoryManager::free(ManagedObject *) {
}

void MarkCompactMemoryManager::collectGarbage() {
#if VERBOSE_GC
    IO::writeLine("\nMarkCompactMemoryManager::collectGarbage()");
    size_t oldSize = memory->getSize(), oldObjectCount = objectCount;
#endif

    mark();
    compact();

#if VERBOSE_GC
    IO::writeLine("//freed=%u, freedObjects=%u, objectCount=%u\n", oldSize - memory->getSize(), oldObjectCount - objectCount, objectCount);
#endif
}

void MarkCompactMemoryManager::reallocate() {
    delta = memory->reallocate();
    updatePointers();
}

void MarkCompactMemoryManager::initialize() {
    memory = new ByteArray(InitialCapacity);
    objectCount = 0;
    delta = 0;
}

void MarkCompactMemoryManager::finalize() {
#if VERBOSE_GC
    IO::writeLine("\nObject count: %u", objectCount);
    IO::writeLine("Memory used: %u", memory->getSize());
    IO::writeLine("Total memory: %u", memory->getCapacity());
    IO::writeLine("\nSemispaceMemoryManager::finalize()");
#endif

    uint8_t *object = memory->getData();

    for (size_t i = 0, size = 0; i < objectCount; i++, object += size) {
        size = reinterpret_cast<ManagedObject *>(object)->getSize();
        reinterpret_cast<ManagedObject *>(object)->finalize();
    }

    delete memory;
}

void MarkCompactMemoryManager::updatePointers() {
#if VERBOSE_GC
    IO::writeLine("MarkCompactMemoryManager::updatePointers() //delta=%i\n", delta);
#endif

    uint8_t *object = memory->getData();

    for (size_t i = 0; i < objectCount; i++, object += reinterpret_cast<ManagedObject *>(object)->getSize())
        reinterpret_cast<ManagedObject *>(object)->mapOnReferences(updateReference);

    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->ptr)
            updateReference(p->ptr);
}

void MarkCompactMemoryManager::mark() {
    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->ptr && !p->ptr->hasFlag(ManagedObject::FlagMark))
            mark(p->ptr);
}

void MarkCompactMemoryManager::compact() {
    uint8_t *object, *free;
    object = free = memory->getData();

    for (size_t i = 0; i < objectCount; i++, object += reinterpret_cast<ManagedObject *>(object)->getSize())
        if (reinterpret_cast<ManagedObject *>(object)->hasFlag(ManagedObject::FlagMark)) {
            reinterpret_cast<ManagedObject *>(object)->setForwardAddress(reinterpret_cast<ManagedObject *>(free));
            free += reinterpret_cast<ManagedObject *>(object)->getSize();
        }

    object = memory->getData();

    for (size_t i = 0; i < objectCount; i++, object += reinterpret_cast<ManagedObject *>(object)->getSize())
        if (reinterpret_cast<ManagedObject *>(object)->hasFlag(ManagedObject::FlagMark))
            reinterpret_cast<ManagedObject *>(object)->mapOnReferences(forwardReference);

    for (Ptr<ManagedObject> *p = reinterpret_cast<Ptr<ManagedObject> *>(pointers); p; p = p->next)
        if (p->ptr && p->ptr->hasFlag(ManagedObject::FlagMark))
            forwardReference(p->ptr);

    object = memory->getData();

    int freeCount = 0, freeSize = 0;

    for (size_t i = 0, size = 0; i < objectCount; i++, object += size) {
        size = reinterpret_cast<ManagedObject *>(object)->getSize();

        if (reinterpret_cast<ManagedObject *>(object)->hasFlag(ManagedObject::FlagMark)) {
            uint8_t *dst = reinterpret_cast<uint8_t *>(reinterpret_cast<ManagedObject *>(object)->getForwardAddress());

            memmove(dst, object, size);

            reinterpret_cast<ManagedObject *>(dst)->removeFlag(ManagedObject::FlagMark);
            reinterpret_cast<ManagedObject *>(dst)->setForwardAddress(0);
        } else {
            freeSize += size;
            freeCount++;

            reinterpret_cast<ManagedObject *>(object)->finalize();
        }
    }

    memory->free(freeSize);
    objectCount -= freeCount;
}

void MarkCompactMemoryManager::mark(ManagedObject *object) {
    object->setFlag(ManagedObject::FlagMark);
    object->mapOnReferences(markReference);
}

void MarkCompactMemoryManager::updateReference(ManagedObject *&ref) {
    ref = reinterpret_cast<ManagedObject *>(reinterpret_cast<uint8_t *>(ref) + delta);
}

void MarkCompactMemoryManager::markReference(ManagedObject *&ref) {
    if (!ref->hasFlag(ManagedObject::FlagMark))
        mark(ref);
}

void MarkCompactMemoryManager::forwardReference(ManagedObject *&ref) {
    ref = ref->getForwardAddress();
}
}

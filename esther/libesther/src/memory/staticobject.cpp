#include "memory/staticobject.h"

#include <new>

#include "memory/memorymanager.h"

namespace es {

StaticObject *StaticObject::create(int refCount) {
    ManagedObject *object = MemoryManager::allocate(sizeof(StaticObject) + refCount * sizeof(ManagedObject *));
    new (object) StaticObject(refCount);
    new (reinterpret_cast<uint8_t *>(object) + sizeof(StaticObject)) ManagedObject *[refCount] { 0 };
    return static_cast<StaticObject *>(object);
}

ManagedObject *&StaticObject::field(int index) {
    return *reinterpret_cast<ManagedObject **>(reinterpret_cast<uint8_t *>(this) + sizeof(*this) + index * sizeof(ManagedObject *));
}

void StaticObject::mapOnReferences(void (*f)(ManagedObject *&)) {
    for (int i = 0; i < refCount; i++)
        if (field(i))
            f(field(i));
}

size_t StaticObject::getSize() const {
    return sizeof(*this) + refCount * sizeof(ManagedObject *);
}

StaticObject::StaticObject(int refCount)
    : refCount(refCount) {
    for (int i = 0; i < refCount; i++)
        field(i) = 0;
}
}

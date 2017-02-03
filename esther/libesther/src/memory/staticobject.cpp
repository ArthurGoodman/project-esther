#include "staticobject.h"

#include "memory/memorymanager.h"

StaticObject *StaticObject::create(int refCount) {
    ManagedObject *object = MemoryManager::allocate(sizeof(StaticObject) + refCount * sizeof(ManagedObject *));
    new (object) StaticObject(refCount);
    new (reinterpret_cast<byte *>(object) + sizeof(StaticObject)) ManagedObject *[refCount] { 0 };
    return static_cast<StaticObject *>(object);
}

ManagedObject *&StaticObject::field(int index) {
    return *reinterpret_cast<ManagedObject **>(reinterpret_cast<byte *>(this) + sizeof(*this) + index * sizeof(ManagedObject *));
}

void StaticObject::mapOnReferences(void (*f)(ManagedObject *&)) {
    for (int i = 0; i < refCount; i++)
        if (field(i))
            f(field(i));
}

int StaticObject::getSize() const {
    return sizeof(*this) + refCount * sizeof(ManagedObject *);
}

StaticObject::StaticObject(int refCount)
    : refCount(refCount) {
    for (int i = 0; i < refCount; i++)
        field(i) = 0;
}

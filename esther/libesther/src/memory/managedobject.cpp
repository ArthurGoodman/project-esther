#include "managedobject.h"

#include "memory/memorymanager.h"

void *ManagedObject::operator new(uint size) noexcept {
    return static_cast<void *>(MemoryManager::allocate(size));
}

void *ManagedObject::operator new(uint, void *p) noexcept {
    return p;
}

void ManagedObject::operator delete(void *p) noexcept {
    MemoryManager::free(static_cast<ManagedObject *>(p));
}

ManagedObject::ManagedObject()
    : flags(0)
    , forwardAddress(nullptr) {
}

ManagedObject::~ManagedObject() {
}

void ManagedObject::finalize() {
}

void ManagedObject::mapOnReferences(void (*)(ManagedObject *&)) {
}

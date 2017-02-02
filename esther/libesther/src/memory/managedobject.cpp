#include "managedobject.h"

#include "memory/memorymanager.h"

void *ManagedObject::operator new(uint size) noexcept {
    return static_cast<void *>(MemoryManager::instance()->allocate(size));
}

void *ManagedObject::operator new(uint, void *p) noexcept {
    return p;
}

void ManagedObject::operator delete(void *p) noexcept {
    MemoryManager::instance()->free(static_cast<ManagedObject *>(p));
}

ManagedObject::ManagedObject()
    : flags(0)
    , forwardAddress(0) {
}

ManagedObject::~ManagedObject() {
}

void ManagedObject::finalize() {
}

void ManagedObject::mapOnReferences(const std::function<void(ManagedObject *&)> &) {
}

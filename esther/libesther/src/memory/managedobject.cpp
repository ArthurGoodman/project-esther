#include "memory/managedobject.h"

#include "memory/memorymanager.h"

namespace es {

void *ManagedObject::operator new(size_t size) noexcept {
    return static_cast<void *>(MemoryManager::allocate(size));
}

void *ManagedObject::operator new(size_t, void *p) noexcept {
    return p;
}

void ManagedObject::operator delete(void *p) noexcept {
    MemoryManager::free(static_cast<ManagedObject *>(p));
}

void ManagedObject::finalize() {
}
}

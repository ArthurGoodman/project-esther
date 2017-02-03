#include "nomemorymanager.h"

#include <memory>

#include "memory/managedobject.h"

ManagedObject *NoMemoryManager::allocate(uint size, int) {
    return static_cast<ManagedObject *>(malloc(size));
}

void NoMemoryManager::free(ManagedObject *p) {
    ::free(p);
}

void NoMemoryManager::collectGarbage() {
}

void NoMemoryManager::reallocate() {
}

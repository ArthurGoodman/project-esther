#include "nomemorymanager.h"

#include <memory>

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

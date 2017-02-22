#include "memory/nomemorymanager.h"

#include <memory>

namespace es {

ManagedObject *NoMemoryManager::allocate(size_t size, size_t) {
    return static_cast<ManagedObject *>(malloc(size));
}

void NoMemoryManager::free(ManagedObject *p) {
    ::free(p);
}

void NoMemoryManager::collectGarbage() {
}

void NoMemoryManager::registerMapper(Mapper *) {
}
}

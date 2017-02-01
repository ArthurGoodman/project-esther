#include "memorymanager.h"

#include "pointer.h"

#include "nomemorymanager.h"
#include "markcompactmemorymanager.h"
#include "semispacememorymanager.h"

MemoryManager *MemoryManager::instance() {
    static NoMemoryManager instance;
    return &instance;
}

MemoryManager::~MemoryManager() {
}

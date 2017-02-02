#include "memorymanager.h"

#include "memory/pointer.h"

#include "memory/nomemorymanager.h"
#include "memory/markcompactmemorymanager.h"
#include "memory/semispacememorymanager.h"

MemoryManager *MemoryManager::instance() {
    static MarkCompactMemoryManager instance;
    return &instance;
}

MemoryManager::~MemoryManager() {
}

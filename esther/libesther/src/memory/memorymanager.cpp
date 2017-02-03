#include "memorymanager.h"

MemoryManager *MemoryManager::instance() {
    static MemoryManager instance;
    return &instance;
}

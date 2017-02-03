#pragma once

#include "memory/nomemorymanager.h"
#include "memory/markcompactmemorymanager.h"
#include "memory/semispacememorymanager.h"

class MemoryManager : public SemispaceMemoryManager {
    static MemoryManager instance;

public:
    template <class T>
    T *allocateArray(uint32_t size);
};

template <class T>
T *MemoryManager::allocateArray(uint32_t size) {
    return new (allocate(size * sizeof(T), size)) T[size];
}

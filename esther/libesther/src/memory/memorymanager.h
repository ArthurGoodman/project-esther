#pragma once

#include "memory/nomemorymanager.h"
#include "memory/markcompactmemorymanager.h"
#include "memory/semispacememorymanager.h"

class MemoryManager : public MarkCompactMemoryManager {
    static MemoryManager instance;

public:
    template <class T>
    T *allocateArray(uint size);
};

template <class T>
T *MemoryManager::allocateArray(uint size) {
    return new (allocate(size * sizeof(T), size)) T[size];
}

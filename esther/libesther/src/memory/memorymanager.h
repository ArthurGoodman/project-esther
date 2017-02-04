#pragma once

#include "common/config.h"
#include "memory/nomemorymanager.h"
#include "memory/markcompactmemorymanager.h"
#include "memory/semispacememorymanager.h"

namespace es {

class MemoryManager : public
#ifdef GC
                      SemispaceMemoryManager
#else
                      NoMemoryManager
#endif
{
    static MemoryManager instance;

public:
    template <class T>
    T *allocateArray(uint32_t size);
};

template <class T>
T *MemoryManager::allocateArray(uint32_t size) {
    return new (allocate(size * sizeof(T), size)) T[size];
}
}

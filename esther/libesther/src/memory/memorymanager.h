#pragma once

#include "common/config.h"

#include "memory/conservativememorymanager.h"
#include "memory/markcompactmemorymanager.h"
#include "memory/semispacememorymanager.h"
#include "memory/nomemorymanager.h"

namespace es {

class MemoryManager : public
#ifdef MEM_MANAGEMENT
                      ConservativeMemoryManager
#else
                      NoMemoryManager
#endif
{
    static MemoryManager instance;

public:
    template <class T>
    T *allocateArray(size_t size);
};

template <class T>
T *MemoryManager::allocateArray(size_t size) {
    return new (allocate(size * sizeof(T), size)) T[size];
}
}

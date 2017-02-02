#pragma once

#include "common/common.h"
#include "memory/pointer.h"

class ManagedObject;

class MemoryManager {
public:
    static MemoryManager *instance();

    template <class T>
    T *allocateArray(uint size);

    virtual ~MemoryManager();

    virtual ManagedObject *allocate(uint size, int count = 1) = 0;
    virtual void free(ManagedObject *p) = 0;

    virtual void collectGarbage() = 0;
    virtual void reallocate() = 0;
};

template <class T>
T *MemoryManager::allocateArray(uint size) {
    return new (instance()->allocate(size * sizeof(T), size)) T[size];
}

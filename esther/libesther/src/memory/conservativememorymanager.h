#pragma once

#include <cstdint>
#include <vector>

#include "common/config.h"

#ifdef MEM_MANAGEMENT

namespace es {

class ManagedObject;
class ByteArray;

class ConservativeMemoryManager {
    static const size_t InitialHeapSize = 10000;
    static const double HeapSizeMultiplier;

    static ConservativeMemoryManager *man;

    std::vector<ByteArray *> heaps;
    size_t objectCount, memoryUsed;

public:
    ConservativeMemoryManager();
    ~ConservativeMemoryManager();

    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    void initialize();
    void finalize();

    ManagedObject *findFreeSpace(size_t size);
    ManagedObject *addHeap();
    void claimFreeSpace(ManagedObject *freeSpace, size_t size);
};
}

#endif

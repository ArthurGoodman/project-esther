#pragma once

#include <cstdint>
#include <vector>
#include <queue>
#include <cmath>

#include "common/config.h"

#if defined(MEM_MANAGEMENT) && defined(CONSERVATIVE_GC)

namespace es {

class ManagedObject;
class ObjectHeader;

class ConservativeMemoryManager {
    struct FreeObject {
        ObjectHeader *header;
        size_t heapIndex;
    };

    struct CompareObjects {
        bool operator()(const FreeObject &a, const FreeObject &b);
    };

    static const size_t InitialHeapSize;
    static const double HeapSizeMultiplier;

    static ConservativeMemoryManager *man;

    std::vector<uint8_t *> heaps;
    std::vector<uint8_t *> bitmaps;

    std::vector<uint32_t> heapSizes;

    size_t objectCount, memoryUsed;
    std::priority_queue<FreeObject, std::vector<FreeObject>, CompareObjects> freeObjects;
    uint32_t *stackBottom, *stackTop;

public:
    ConservativeMemoryManager();
    ~ConservativeMemoryManager();

    static void initStack(uint32_t *stackBottom);

    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    void initialize();
    void finalize();

    bool enoughSpace(size_t size);
    int isPointerToHeap(void *p);

    void mark();
    void markRange(uint32_t *start, size_t n);
    void mark(ManagedObject *object, int heapIndex = -1);

    void sweep();

    void addHeap();
    ManagedObject *claimFreeSpace(size_t size);

    void markFree(uint8_t *p, size_t size, size_t heapIndex);

    static void markReference(ManagedObject *&ref);

    static size_t bitmapSize(size_t size);
    static size_t bitmapByte(size_t i);
    static size_t bitmapBit(size_t i);
};

inline size_t ConservativeMemoryManager::bitmapSize(size_t size) {
    return size % 32 ? size / 32 + 1 : size / 32;
}

inline size_t ConservativeMemoryManager::bitmapByte(size_t i) {
    return i / 32;
}

inline size_t ConservativeMemoryManager::bitmapBit(size_t i) {
    return (i / 4) % 8;
}
}

#endif

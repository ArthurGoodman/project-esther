#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <vector>

#include "common/config.h"

#if defined(MEM_MANAGEMENT) && defined(CONSERVATIVE_GC)

namespace es {

#ifdef __x86_64
typedef uint64_t ptr_t;
typedef uint64_t *ptr_ptr_t;
#elif __i386
typedef uint32_t ptr_t;
typedef uint32_t *ptr_ptr_t;
#endif

class Mapper;
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

    typedef std::priority_queue<FreeObject, std::vector<FreeObject>, CompareObjects> FreeObjectQueue;

    static const size_t InitialHeapSize;
    static const double HeapSizeMultiplier;

    static ConservativeMemoryManager *man;

    std::vector<uint8_t *> heaps;
    std::vector<uint32_t> heapSizes;
    std::vector<uint8_t *> bitmaps;

    uint8_t *heapMin, *heapMax;

    size_t objectCount, memoryUsed;

    FreeObjectQueue freeObjects;

    ptr_ptr_t stackBottom, stackTop;

    std::vector<Mapper *> mappers;

public:
    ConservativeMemoryManager();
    ~ConservativeMemoryManager();

    static void initStack(ptr_ptr_t stackBottom);

    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();

    static void registerMapper(Mapper *mapper);

private:
    void initialize();
    void finalize();

    bool enoughSpace(size_t size);

    bool isValidPtr(uint8_t *p);

    void mark();

    void markRange(ptr_ptr_t start, size_t n);

    void mark(ManagedObject *object);

    void sweep();

    void addHeap();
    ManagedObject *claimFreeSpace(size_t size);

    void markFree(uint8_t *p, size_t size, size_t heapIndex);

    void markAsAllocation(uint8_t *p, size_t heapIndex);
    bool isAllocation(uint8_t *p, size_t heapIndex);

    static void markReference(ManagedObject *&ref);

    static size_t bitmapSize(size_t size);
    static size_t bitmapByte(size_t i);
    static size_t bitmapBit(size_t i);
};

inline void ConservativeMemoryManager::markAsAllocation(uint8_t *p, size_t heapIndex) {
    size_t headerByte = p - heaps[heapIndex];
    bitmaps[heapIndex][bitmapByte(headerByte)] |= 1 << bitmapBit(headerByte);
}

inline bool ConservativeMemoryManager::isAllocation(uint8_t *p, size_t heapIndex) {
    size_t headerByte = p - heaps[heapIndex];
    return bitmaps[heapIndex][bitmapByte(headerByte)] & (1 << bitmapBit(headerByte));
}

inline size_t ConservativeMemoryManager::bitmapSize(size_t size) {
    return size % sizeof(void *) / 8 ? size / sizeof(void *) / 8 + 1 : size / sizeof(void *) / 8;
}

inline size_t ConservativeMemoryManager::bitmapByte(size_t i) {
    return i / sizeof(void *) / 8;
}

inline size_t ConservativeMemoryManager::bitmapBit(size_t i) {
    return i / sizeof(void *) % 8;
}
}

#endif

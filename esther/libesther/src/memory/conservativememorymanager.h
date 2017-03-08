#pragma once

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <queue>
#include <vector>

#include "common/config.h"

#if defined(MEM_MANAGEMENT) && defined(CONSERVATIVE_GC)

namespace es {

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

#ifdef __x86_64
    uint64_t *stackBottom, *stackTop;
#elif __i386
    uint32_t *stackBottom, *stackTop;
#endif

    std::vector<Mapper *> mappers;

public:
    ConservativeMemoryManager();
    ~ConservativeMemoryManager();

#ifdef __x86_64
    static void initStack(uint64_t *stackBottom);
#elif __i386
    static void initStack(uint32_t *stackBottom);
#endif

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

#ifdef __x86_64
    void markRange(uint64_t *start, size_t n);
#elif __i386
    void markRange(uint32_t *start, size_t n);
#endif

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

#ifdef __x86_64
inline size_t ConservativeMemoryManager::bitmapSize(size_t size) {
    return size % 64 ? size / 64 + 1 : size / 64;
}

inline size_t ConservativeMemoryManager::bitmapByte(size_t i) {
    return i / 64;
}

inline size_t ConservativeMemoryManager::bitmapBit(size_t i) {
    return (i / 8) % 8;
}
#elif __i386
inline size_t ConservativeMemoryManager::bitmapSize(size_t size) {
    return size % 32 ? size / 32 + 1 : size / 32;
}

inline size_t ConservativeMemoryManager::bitmapByte(size_t i) {
    return i / 32;
}

inline size_t ConservativeMemoryManager::bitmapBit(size_t i) {
    return (i / 4) % 8;
}
#endif
}

#endif

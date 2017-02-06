#pragma once

#include <cstdint>

#include "common/config.h"

#ifdef MEM_MANAGEMENT

namespace es {

class ManagedObject;
class ByteArray;

class MarkCompactMemoryManager {
    static const size_t InitialCapacity = 1 << 10;

    static MarkCompactMemoryManager *man;

    ByteArray *memory;
    size_t objectCount;
    int delta;

public:
    MarkCompactMemoryManager();
    ~MarkCompactMemoryManager();

    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    void initialize();
    void finalize();

    void updatePointers();

    void mark();
    void compact();

    void mark(ManagedObject *object);

    static void updateReference(ManagedObject *&ref);
    static void markReference(ManagedObject *&ref);
    static void forwardReference(ManagedObject *&ref);
};
}

#endif

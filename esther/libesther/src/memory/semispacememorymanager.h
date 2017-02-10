#pragma once

#include <cstdint>

#include "common/config.h"

#if 0

namespace es {

class ManagedObject;
class ByteArray;

class SemispaceMemoryManager {
    static const size_t InitialCapacity = 1 << 10;

    static SemispaceMemoryManager *man;

    ByteArray *memory;

    size_t objectCount, memoryUsed, capacity;
    int delta;

    uint8_t *toSpace, *fromSpace, *allocPtr;

public:
    SemispaceMemoryManager();
    ~SemispaceMemoryManager();

    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    void initialize();
    void finalize();

    bool enoughSpace(int size);

    ManagedObject *copy(ManagedObject *object);
    void expand();

    static void updateReference(ManagedObject *&ref);
};
}

#endif

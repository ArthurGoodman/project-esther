#pragma once

#include <cstdint>

namespace es {

class ManagedObject;

class MarkCompactMemoryManager {
    static const int InitialCapacity = 1 << 10;

public:
    MarkCompactMemoryManager();
    ~MarkCompactMemoryManager();

    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    static void initialize();
    static void finalize();

    static void updatePointers();

    static void mark();
    static void compact();

    static void mark(ManagedObject *object);

    static void updateReference(ManagedObject *&ref);
    static void markReference(ManagedObject *&ref);
    static void forwardReference(ManagedObject *&ref);
};
}

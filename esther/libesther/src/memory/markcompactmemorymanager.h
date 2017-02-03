#pragma once

#include "common/bytearray.h"
#include "memory/managedobject.h"

class MarkCompactMemoryManager {
public:
    MarkCompactMemoryManager();
    ~MarkCompactMemoryManager();

    static ManagedObject *allocate(uint size, int count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    static void initialize();
    static void finalize();

    static void updatePointers();
    static void updatePointer(ManagedObject *&pointer);

    static void mark();
    static void compact();

    static void updatePointers(ManagedObject *object);
    static void forwardPointers(ManagedObject *object);
    static void mark(ManagedObject *object);

    static void markReference(ManagedObject *&ref);
    static void forwardReference(ManagedObject *&ref);
};

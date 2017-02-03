#pragma once

#include "common/bytearray.h"

class ManagedObject;

class SemispaceMemoryManager {
    static const int InitialCapacity = 1 << 10;

public:
    SemispaceMemoryManager();
    ~SemispaceMemoryManager();

    static ManagedObject *allocate(uint size, int count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    static void initialize();
    static void finalize();

    static bool enoughSpace(int size);

    static ManagedObject *copy(ManagedObject *object);
    static void expand();

    static void updateReference(ManagedObject *&ref);
};

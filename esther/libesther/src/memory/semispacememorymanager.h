#pragma once

#include <cstdint>

#include "common/config.h"

#ifdef GC

namespace es {

class ManagedObject;

class SemispaceMemoryManager {
    static const int InitialCapacity = 1 << 10;

public:
    SemispaceMemoryManager();
    ~SemispaceMemoryManager();

    static ManagedObject *allocate(size_t size, size_t count = 1);
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
}

#endif

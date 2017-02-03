#pragma once

#include <cstdint>

namespace es {

class ManagedObject;

class NoMemoryManager {
public:
    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();
};
}

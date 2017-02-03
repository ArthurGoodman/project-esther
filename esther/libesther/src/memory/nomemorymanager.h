#pragma once

#include <cstdint>

class ManagedObject;

class NoMemoryManager {
public:
    static ManagedObject *allocate(uint32_t size, int count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();
};

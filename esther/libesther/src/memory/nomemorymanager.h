#pragma once

#include "common/common.h"

class ManagedObject;

class NoMemoryManager {
public:
    static ManagedObject *allocate(uint size, int count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();
};

#pragma once

#include <cstdint>

#include "common/config.h"

#ifdef MEM_MANAGEMENT

namespace es {

class ManagedObject;

class ConservativeMemoryManager {
    static const size_t HeapSize = 1 << 10;

public:
    ConservativeMemoryManager();
    ~ConservativeMemoryManager();

    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    static void initialize();
    static void finalize();
};
}

#endif

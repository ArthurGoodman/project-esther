#pragma once

#include <cstdint>

#include "common/config.h"

#ifdef MEM_MANAGEMENT

namespace es {

class ManagedObject;

class ConservativeMemoryManager {
    static const int InitialCapacity = 1 << 10;

public:
    ConservativeMemoryManager();
    ~ConservativeMemoryManager();

    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();
    static void reallocate();

private:
    void initialize();
    void finalize();
};
}

#endif

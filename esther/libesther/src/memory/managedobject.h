#pragma once

#include <cstddef>
#include <cstdint>

#include "memory/mapper.h"

namespace es {

class ManagedObject : public Mapper {
public:
    static void *operator new(size_t size) noexcept;
    static void *operator new(size_t size, void *p) noexcept;
    static void operator delete(void *p) noexcept;

    virtual void finalize();
};
}

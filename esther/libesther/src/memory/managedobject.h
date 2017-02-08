#pragma once

#include <cstdint>

namespace es {

class ManagedObject {
public:
    static void *operator new(size_t size) noexcept;
    static void *operator new(size_t size, void *p) noexcept;
    static void operator delete(void *p) noexcept;

    virtual ~ManagedObject();

    virtual void finalize();
    virtual void mapOnReferences(void (*f)(ManagedObject *&));
};
}

#pragma once

#include <cstddef>
#include <cstdint>

namespace es {

class Mapper;
class ManagedObject;

class NoMemoryManager {
public:
    static ManagedObject *allocate(size_t size, size_t count = 1);
    static void free(ManagedObject *p);

    static void collectGarbage();

    static void registerMapper(Mapper *mapper);
};
}

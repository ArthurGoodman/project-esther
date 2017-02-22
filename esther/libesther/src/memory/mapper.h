#pragma once

namespace es {

class ManagedObject;

class Mapper {
public:
    virtual ~Mapper();

    virtual void mapOnReferences(void (*f)(ManagedObject *&));
};
}

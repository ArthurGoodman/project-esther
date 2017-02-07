#pragma once

#include "memory/managedobject.h"

namespace es {

class StaticObject : public ManagedObject {
    int refCount;

public:
    static StaticObject *create(int refCount);

    ManagedObject *&field(int index);

    void mapOnReferences(void (*f)(ManagedObject *&)) override;

private:
    StaticObject(int refCount);
};
}

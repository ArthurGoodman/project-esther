#pragma once

#include "memory/managedobject.h"

class StaticObject : public ManagedObject {
    int refCount;

public:
    static StaticObject *create(int refCount);

    ManagedObject *&field(int index);

    void mapOnReferences(void (*f)(ManagedObject *&)) override;
    int getSize() const override;

private:
    StaticObject(int refCount);
};

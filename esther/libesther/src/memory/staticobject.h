#pragma once

#include "memory/managedobject.h"

class StaticObject : public ManagedObject {
    int refCount;

public:
    static StaticObject *create(int refCount);

    ManagedObject *&field(int index);

    void mapOnReferences(const std::function<void(ManagedObject *&)> &f) override;
    int getSize() const override;

private:
    StaticObject(int refCount);
};

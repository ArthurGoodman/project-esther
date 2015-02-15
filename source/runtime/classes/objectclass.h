#pragma once
#include "common.h"

#include "rootclass.h"

class ObjectClass : public RootClass {
public:
    ObjectClass();

    Object *newInstance();

    void setupMethods();
};

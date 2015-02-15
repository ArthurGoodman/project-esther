#pragma once
#include "common.h"

#include "rootclass.h"

class FloatClass : public RootClass {
public:
    FloatClass();

    Object *newInstance();

    void setupMethods();
};

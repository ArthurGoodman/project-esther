#pragma once
#include "common.h"

#include "rootclass.h"

class FunctionClass : public RootClass {
public:
    FunctionClass();

    Object *newInstance();

    void setupMethods();
};

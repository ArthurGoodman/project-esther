#pragma once
#include "common.h"

#include "class.h"

class FunctionClass : public Class {
public:
    FunctionClass();

    Object *newInstance();

    void setupMethods();
};

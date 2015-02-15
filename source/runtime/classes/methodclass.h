#pragma once
#include "common.h"

#include "class.h"

class MethodClass : public Class {
public:
    MethodClass();

    Object *newInstance();

    void setupMethods();
};

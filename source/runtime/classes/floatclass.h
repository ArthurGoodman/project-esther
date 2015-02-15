#pragma once
#include "common.h"

#include "class.h"

class FloatClass : public Class {
public:
    FloatClass();

    Object *newInstance();

    void setupMethods();
};

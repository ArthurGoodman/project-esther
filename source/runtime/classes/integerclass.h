#pragma once
#include "common.h"

#include "class.h"

class IntegerClass : public Class {
public:
    IntegerClass();

    Object *newInstance();

    void setupMethods();
};

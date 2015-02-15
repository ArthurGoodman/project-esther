#pragma once
#include "common.h"

#include "rootclass.h"

class IntegerClass : public RootClass {
public:
    IntegerClass();

    Object *newInstance();

    void setupMethods();
};

#pragma once
#include "common.h"

#include "rootclass.h"

class BooleanClass : public RootClass {
public:
    BooleanClass();

    Object *newInstance();

    void setupMethods();
};

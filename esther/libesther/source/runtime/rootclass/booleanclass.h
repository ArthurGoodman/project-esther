#pragma once

#include "rootclass.h"

class BooleanClass : public RootClass {
public:
    Object *createTrue();
    Object *createFalse();

    void setupMethods();
};

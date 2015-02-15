#pragma once
#include "common.h"

#include "rootclass.h"

class StringClass : public RootClass {
public:
    StringClass();

    Object *newInstance();

    void setupMethods();
};

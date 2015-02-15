#pragma once
#include "common.h"

#include "rootclass.h"

class ContextClass : public RootClass {
public:
    ContextClass();

    Object *newInstance();

    void setupMethods();
};

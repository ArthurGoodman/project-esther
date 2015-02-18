#pragma once
#include "common.h"

#include "rootclass.h"

class InterfaceClass : public RootClass
{
public:
    InterfaceClass();

    Object *newInstance();

    void setupMethods();
};

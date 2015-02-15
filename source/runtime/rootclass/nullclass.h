#pragma once
#include "common.h"

#include "rootclass.h"

class NullClass : public RootClass
{
public:
    NullClass();

    Object *newInstance();

    void setupMethods();
};

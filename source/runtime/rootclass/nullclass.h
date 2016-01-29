#pragma once

#include "rootclass.h"

class NullClass : public RootClass
{
public:
    NullClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

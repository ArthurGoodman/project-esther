#pragma once
#include "common.h"

#include "rootclass.h"

class FunctionClass : public RootClass {
public:
    FunctionClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

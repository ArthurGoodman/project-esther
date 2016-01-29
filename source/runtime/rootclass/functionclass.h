#pragma once

#include "rootclass.h"

class FunctionClass : public RootClass {
public:
    FunctionClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

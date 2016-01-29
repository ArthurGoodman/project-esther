#pragma once

#include "rootclass.h"

class MethodClass : public RootClass {
public:
    MethodClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

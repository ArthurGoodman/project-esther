#pragma once
#include "common.h"

#include "rootclass.h"

class MethodClass : public RootClass {
public:
    MethodClass();

    void setupMethods();

protected:
    Object *createNewInstance();
};

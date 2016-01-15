#pragma once

#include "rootclass.h"

class OverloadedMethodClass : public RootClass {
public:
    OverloadedMethodClass();

    void setupMethods();

protected:
    Object *createNewInstance();
};

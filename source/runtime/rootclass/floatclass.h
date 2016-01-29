#pragma once

#include "rootclass.h"

class FloatClass : public RootClass {
public:
    FloatClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

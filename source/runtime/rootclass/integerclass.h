#pragma once

#include "rootclass.h"

class IntegerClass : public RootClass {
public:
    IntegerClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

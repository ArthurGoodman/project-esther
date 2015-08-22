#pragma once
#include "common.h"

#include "rootclass.h"

class IntegerClass : public RootClass {
public:
    IntegerClass();

    void setupMethods();

protected:
    Object *createNewInstance();
};

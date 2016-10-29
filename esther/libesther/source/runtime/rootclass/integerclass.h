#pragma once

#include "rootclass.h"

class IntegerClass : public RootClass {
public:
    Object *createInteger(int value);

    void setupMethods();

protected:
    Object *createNewInstance();
};

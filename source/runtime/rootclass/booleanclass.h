#pragma once

#include "rootclass.h"

class BooleanClass : public RootClass {
public:
    BooleanClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

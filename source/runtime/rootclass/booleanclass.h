#pragma once
#include "common.h"

#include "rootclass.h"

class BooleanClass : public RootClass {
public:
    BooleanClass();

    void setupMethods();

protected:
    Object *createNewInstance();
};

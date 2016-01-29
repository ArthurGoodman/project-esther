#pragma once

#include "rootclass.h"

class ObjectClass : public RootClass {
public:
    ObjectClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

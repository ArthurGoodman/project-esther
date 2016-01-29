#pragma once

#include "rootclass.h"

class StringClass : public RootClass {
public:
    StringClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

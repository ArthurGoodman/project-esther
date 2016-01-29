#pragma once

#include "rootclass.h"

class RangeClass : public RootClass {
public:
    RangeClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

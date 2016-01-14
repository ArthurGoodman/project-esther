#pragma once
#include "common.h"

#include "rootclass.h"

class RangeClass : public RootClass {
public:
    RangeClass();

    void setupMethods();

protected:
    Object *createNewInstance();
};

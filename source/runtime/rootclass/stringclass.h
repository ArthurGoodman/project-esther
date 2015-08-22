#pragma once
#include "common.h"

#include "rootclass.h"

class StringClass : public RootClass {
public:
    StringClass();

    void setupMethods();

protected:
    Object *createNewInstance();
};

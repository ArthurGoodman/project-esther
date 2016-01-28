#pragma once
#include "common.h"

#include "rootclass.h"

class ClassClass : public RootClass {
public:
    ClassClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

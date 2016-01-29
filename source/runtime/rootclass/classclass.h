#pragma once

#include "rootclass.h"

class ClassClass : public RootClass {
public:
    ClassClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

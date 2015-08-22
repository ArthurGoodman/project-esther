#pragma once
#include "common.h"

#include "rootclass.h"

class ContextClass : public RootClass {
public:
    ContextClass();

    void setupMethods();

protected:
    Object *createNewInstance();
};

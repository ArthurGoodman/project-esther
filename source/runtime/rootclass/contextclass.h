#pragma once

#include "rootclass.h"

class ContextClass : public RootClass {
public:
    ContextClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

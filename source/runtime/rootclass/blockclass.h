#pragma once

#include "rootclass.h"

class BlockClass : public RootClass {
public:
    BlockClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

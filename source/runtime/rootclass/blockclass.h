#pragma once

#include "rootclass.h"

class BlockClass : public RootClass {
public:
    BlockClass();

    Object *newInstance();

    void setupMethods();
};

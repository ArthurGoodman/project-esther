#pragma once

#include "rootclass.h"

class NullClass : public RootClass {
public:
    Object *createNull();

    void setupMethods();
};

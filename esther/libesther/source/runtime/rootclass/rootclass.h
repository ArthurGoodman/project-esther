#pragma once

#include "class.h"

class RootClass : public Class {
public:
    RootClass();

    virtual void setupMethods() = 0;
};

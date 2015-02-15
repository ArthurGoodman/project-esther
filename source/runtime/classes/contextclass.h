#pragma once
#include "common.h"

#include "class.h"

class ContextClass : public Class {
public:
    ContextClass();

    Object *newInstance();

    void setupMethods();
};

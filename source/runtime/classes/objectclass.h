#pragma once
#include "common.h"

#include "class.h"

class ObjectClass : public Class {
public:
    ObjectClass();

    Object *newInstance();

    void setupMethods();
};

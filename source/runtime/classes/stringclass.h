#pragma once
#include "common.h"

#include "class.h"

class StringClass : public Class {
public:
    StringClass();

    Object *newInstance();

    void setupMethods();
};

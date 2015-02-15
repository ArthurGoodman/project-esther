#pragma once
#include "common.h"

#include "class.h"

class ClassClass : public Class {
public:
    ClassClass();

    Object *newInstance();

    void setupMethods();
};

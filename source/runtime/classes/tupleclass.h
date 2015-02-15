#pragma once
#include "common.h"

#include "class.h"

class TupleClass : public Class {
public:
    TupleClass();

    Object *newInstance();

    void setupMethods();
};

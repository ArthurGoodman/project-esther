#pragma once
#include "common.h"

#include "rootclass.h"

class TupleClass : public RootClass {
public:
    TupleClass();

    Object *newInstance();

    void setupMethods();
};

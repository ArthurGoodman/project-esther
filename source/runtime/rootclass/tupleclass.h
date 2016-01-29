#pragma once

#include "rootclass.h"

class TupleClass : public RootClass {
public:
    TupleClass();

    void setupMethods();

protected:
    IObject *createNewInstance();
};

#pragma once

#include "rootclass.h"

class FloatClass : public RootClass {
public:
    Object *createFloat(double value);

    void setupMethods();

protected:
    Object *createNewInstance();
};

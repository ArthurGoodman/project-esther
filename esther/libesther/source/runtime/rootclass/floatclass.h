#pragma once

#include "rootclass.h"

class ValueObject;

class FloatClass : public RootClass {
    friend class Runtime;

public:
    ValueObject *createFloat(double value);

protected:
    Object *createNewInstance();

    void setupMethods();

private:
    FloatClass(Runtime *runtime);
};

#pragma once

#include "class.h"

class ValueObject;

class FloatClass : public Class {
    friend class ClassClass;

public:
    ValueObject *createFloat(double value);

protected:
    Object *createNewInstance();

private:
    FloatClass(Class *objectClass);
};

#pragma once

#include "class.h"

class ValueObject;

class IntegerClass : public Class {
    friend class Runtime;

public:
    ValueObject *createInteger(int value);

protected:
    Object *createNewInstance();

private:
    IntegerClass(Class *objectClass);
};

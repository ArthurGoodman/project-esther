#pragma once
#include "common.h"

#include "object.h"

class Parameter : public Object {
    Class *type;
    string name;
    IObject *value;

public:
    Parameter(Class *type, string name, IObject *value);

    Class *getType();
    string getName();
    IObject *getValue();

    bool equals(Parameter *other);

    IObject *clone();
};

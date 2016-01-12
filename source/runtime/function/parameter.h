#pragma once
#include "common.h"

#include "object.h"

class Parameter : public Object {
    Class *type;
    string name;
    Object *value;

public:
    Parameter(Class *type, string name, Object *value);

    Class *getType();
    string getName();
    Object *getValue();

    bool equals(Parameter *other);

    Object *clone();
};

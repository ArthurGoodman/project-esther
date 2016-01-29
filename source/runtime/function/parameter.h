#pragma once

#include "object.h"

class Parameter : public Object {
    Class *type;
    std::string name;
    IObject *value;

public:
    Parameter(Class *type, const std::string &name, IObject *value);

    Class *getType();
    std::string getName();
    IObject *getValue();

    bool equals(Parameter *other);

    IObject *clone();
};

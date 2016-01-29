#pragma once

#include "object.h"

class True : public Object {
public:
    True();

    bool isTrue();
    bool isFalse();

    std::string toString();

    IObject *clone();
};

#pragma once
#include "common.h"

#include "object.h"

class True : public Object {
public:
    True();

    bool isTrue();
    bool isFalse();

    string toString();

    IObject *clone();
};

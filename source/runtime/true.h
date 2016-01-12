#pragma once
#include "common.h"

#include "object.h"

class True : public Object {
public:
    True();

    bool isTrue();
    bool isFalse();
    bool isNull();

    string toString();

    Object *clone();
};

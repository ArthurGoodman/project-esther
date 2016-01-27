#pragma once
#include "common.h"

#include "object.h"

class Null : public Object {
public:
    Null();

    bool isTrue();
    bool isFalse();

    string toString();

    Object *clone();
};

#pragma once
#include "common.h"

#include "object.h"

class Null : public Object {
public:
    Null();

    bool isTrue();
    bool isFalse();
    bool isNull();

    string immediateToString();

    Object *clone();
};

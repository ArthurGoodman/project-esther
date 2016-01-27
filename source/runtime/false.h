#pragma once
#include "common.h"

#include "object.h"

class False : public Object {
public:
    False();

    bool isTrue();
    bool isFalse();

    string toString();

    Object *clone();
};

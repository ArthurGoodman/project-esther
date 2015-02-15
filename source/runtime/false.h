#pragma once
#include "common.h"

#include "object.h"

class False : public Object {
public:
    False();

    bool isTrue();
    bool isFalse();
    bool isNull();

    string toString();
};

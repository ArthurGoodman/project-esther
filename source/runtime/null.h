#pragma once

#include "object.h"

class Null : public Object {
public:
    Null();

    bool isTrue();
    bool isFalse();

    std::string toString();

    IObject *clone();
};

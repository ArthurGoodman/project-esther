#pragma once

#include "object.h"

class False : public Object {
public:
    False();

    bool isTrue();
    bool isFalse();

    std::string toString();

    IObject *clone();
};

#pragma once

#include "object.h"

class Null : public Object {
public:
    Null();

    bool isTrue();

    std::string toString();
};

#pragma once

#include "object.h"

class True : public Object {
public:
    True();

    bool isTrue();

    std::string toString();
};

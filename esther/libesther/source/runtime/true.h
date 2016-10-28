#pragma once

#include "object.h"

class True : public Object {
    friend class BooleanClass;

public:
    bool isTrue();

    std::string toString();

private:
    True(Class *objectClass);
};

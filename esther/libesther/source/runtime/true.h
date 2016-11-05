#pragma once

#include "object.h"

class True : public Object {
    friend class BooleanClass;

public:
    std::string toString();

private:
    True(Class *objectClass);
};

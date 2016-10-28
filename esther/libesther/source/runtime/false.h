#pragma once

#include "object.h"

class False : public Object {
    friend class BooleanClass;

public:
    bool isTrue();

    std::string toString();

private:
    False(Class *objectClass);
};

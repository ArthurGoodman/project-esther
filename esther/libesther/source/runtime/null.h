#pragma once

#include "object.h"

class Null : public Object {
    friend class NullClass;

public:
    bool isTrue();

    std::string toString();

private:
    Null(Class *objectClass);
};

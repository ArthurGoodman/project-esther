#pragma once
#include <common.h>

namespace esther {

class Class;

class Object {
    Class *objectClass;

public:
    Object(Class *objectClass = 0);

    Class *getClass();

    virtual string toString();
};
}

#pragma once
#include "common.h"

#include "object.h"

namespace esther {

class Class;

class Signature : public Object {
    Class *returnType;
    list<Class *> argsTypes;

public:
    Signature(Class *returnType, list<Class *> argsTypes);
};
}

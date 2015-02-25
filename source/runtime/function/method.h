#pragma once
#include "common.h"

#include "function.h"

class Method : public Function {
    bool staticFlag;

public:
    Method(string name, Context *context, Signature *signature, Block *body, Object *self, bool isStatic = false);

    string toString();

    void check(Object *self, Tuple *args);

    bool isStatic();
};

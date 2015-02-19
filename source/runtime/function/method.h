#pragma once
#include "common.h"

#include "function.h"

class Method : public Function {
public:
    Method(string name, Context *context, Signature *signature, list<string> params, Block *body);

    virtual Object *invoke(Object *self, Tuple *args);

    string toString();

    void check(Object *self, Tuple *args);
};

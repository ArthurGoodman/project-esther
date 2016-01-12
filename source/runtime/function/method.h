#pragma once
#include "common.h"

#include "function.h"

class Method : public Function {
    bool staticFlag;
    Object *self;

protected:
    Method(string className, string name, Context *context, Signature *signature, Block *body, Object *self, bool staticFlag = false);

public:
    Method(string name, Context *context, Signature *signature, Block *body, Object *self, bool staticFlag = false);

    bool isStatic();
    Object *getSelf();

    bool suitableFor(Object *self);

    virtual Object *clone();
};

#pragma once
#include "common.h"

#include "function.h"

class Method : public Function {
    bool staticFlag;
    IObject *self;

protected:
    Method(string className, string name, Context *context, Signature *signature, Block *body, IObject *self, bool staticFlag = false);

public:
    Method(string name, Context *context, Signature *signature, Block *body, IObject *self, bool staticFlag = false);

    bool isStatic();
    IObject *getSelf();

    bool suitableFor(IObject *self);

    virtual string toString();

    virtual IObject *clone();
};

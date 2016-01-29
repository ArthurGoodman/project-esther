#pragma once

#include "function.h"

class Method : public Function {
    bool staticFlag;
    IObject *self;

protected:
    Method(const std::string &className, const std::string &name, Context *context, Signature *signature, Block *body, IObject *self, bool staticFlag = false);

public:
    Method(const std::string &name, Context *context, Signature *signature, Block *body, IObject *self, bool staticFlag = false);

    bool isStatic();
    IObject *getSelf();

    bool suitableFor(IObject *self);

    virtual std::string toString();

    virtual IObject *clone();
};

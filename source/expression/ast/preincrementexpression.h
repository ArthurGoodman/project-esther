#pragma once
#include "common.h"

#include "expression.h"

class PreIncrementExpression : public Expression {
    Expression *self;

public:
    PreIncrementExpression(Expression *self);
    ~PreIncrementExpression();

    Object *eval(Context *context);
};

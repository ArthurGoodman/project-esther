#pragma once
#include "common.h"

#include "expression.h"

class PreIncrementExpression : public Expression {
    Expression *self;

public:
    PreIncrementExpression(Expression *self);

    IObject *exec(Context *context);
};

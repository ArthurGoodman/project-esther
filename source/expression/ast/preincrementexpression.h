#pragma once
#include "common.h"

#include "expression.h"

class PreIncrementExpression : public Expression {
    Expression *self;

public:
    PreIncrementExpression(Expression *self);

    Object *eval(Context *context);
};

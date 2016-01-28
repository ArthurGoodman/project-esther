#pragma once
#include "common.h"

#include "expression.h"

class PreDecrementExpression : public Expression {
    Expression *self;

public:
    PreDecrementExpression(Expression *self);

    IObject *exec(Context *context);
};

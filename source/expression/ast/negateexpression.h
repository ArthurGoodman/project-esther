#pragma once
#include "common.h"

#include "expression.h"

class NegateExpression : public Expression {
    Expression *self;

public:
    NegateExpression(Expression *self);

    Object *eval(Context *context);
};

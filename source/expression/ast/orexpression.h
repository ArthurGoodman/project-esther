#pragma once
#include "common.h"

#include "expression.h"

class OrExpression : public Expression {
    Expression *self, *arg;

public:
    OrExpression(Expression *self, Expression *arg);

    Object *exec(Context *context);
};

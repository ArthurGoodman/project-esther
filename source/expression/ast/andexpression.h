#pragma once
#include "common.h"

#include "expression.h"

class AndExpression : public Expression {
    Expression *self, *arg;

public:
    AndExpression(Expression *self, Expression *arg);

    IObject *exec(Context *context);
};

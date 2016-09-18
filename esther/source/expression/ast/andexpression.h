#pragma once

#include "expression.h"

class AndExpression : public Expression {
    Expression *self, *arg;

public:
    AndExpression(Expression *self, Expression *arg);
    ~AndExpression();

    Object *exec(Context *context);
};

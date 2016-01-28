#pragma once
#include "common.h"

#include "expression.h"

class ContextCallExpression : public Expression {
    Expression *self;
    Expression *body;
    list<Expression *> args;

public:
    ContextCallExpression(Expression *self, Expression *body, list<Expression *> args);

    IObject *exec(Context *context);
};

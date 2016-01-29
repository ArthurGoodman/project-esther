#pragma once

#include "expression.h"

class ContextCallExpression : public Expression {
    Expression *self;
    Expression *body;
    std::list<Expression *> args;

public:
    ContextCallExpression(Expression *self, Expression *body, std::list<Expression *> args);

    IObject *exec(Context *context);
};

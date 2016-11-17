#pragma once

#include "expression.h"

class ContextCallExpression : public Expression {
    Expression *self, *body;
    std::list<Expression *> args;
    Context *context;

public:
    ContextCallExpression(Expression *self, Expression *body, const std::list<Expression *> &args, Context *context);
    ~ContextCallExpression();

    Object *exec(Context *context);
};

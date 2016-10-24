#pragma once

#include "expression.h"

class CallExpression : public Expression {
    Expression *self, *body;
    std::list<Expression *> args;

public:
    CallExpression(Expression *self, Expression *body, const std::list<Expression *> &args);

    Object *exec(Context *context);
};

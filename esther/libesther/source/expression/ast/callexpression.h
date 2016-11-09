#pragma once

#include "expression.h"

class CallExpression : public Expression {
    Expression *self, *name;
    std::list<Expression *> args;

public:
    CallExpression(Expression *self, Expression *name, const std::list<Expression *> &args);
    ~CallExpression();

    Object *exec(Context *context);
};

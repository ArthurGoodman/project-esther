#pragma once

#include "expression.h"

class DirectCallExpression : public Expression {
    Expression *self, *name;
    std::list<Expression *> args;

public:
    DirectCallExpression(Expression *self, Expression *name, const std::list<Expression *> &args);
    ~DirectCallExpression();

    Object *exec(Context *context);
};

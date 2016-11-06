#pragma once

#include "expression.h"

class DirectCallExpression : public Expression {
    Expression *self;
    std::string name;
    std::list<Expression *> args;

public:
    DirectCallExpression(Expression *self, const std::string &name, const std::list<Expression *> &args);
    ~DirectCallExpression();

    Object *exec(Context *context);
};

#pragma once

#include "expression.h"

class CallExpression : public Expression {
    Expression *self;
    std::string name;
    std::list<Expression *> args;

public:
    CallExpression(Expression *self, const std::string &name, std::list<Expression *> args);

    IObject *exec(Context *context);
};

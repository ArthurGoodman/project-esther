#pragma once

#include "expression.h"

class CallExpression : public Expression {
    Expression *name;
    std::list<Expression *> args;

public:
    CallExpression(Expression *name, const std::list<Expression *> &args);
    ~CallExpression();

    Object *exec(Context *context);
};

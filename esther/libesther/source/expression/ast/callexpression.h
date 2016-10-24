#pragma once

#include "expression.h"

class CallExpression : public Expression {
    Expression *body;
    std::list<Expression *> args;

public:
    CallExpression(Expression *body, const std::list<Expression *> &args);
    ~CallExpression();

    Object *exec(Context *context);
};

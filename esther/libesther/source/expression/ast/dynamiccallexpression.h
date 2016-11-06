#pragma once

#include "expression.h"

class DynamicCallExpression : public Expression {
    Expression *body;
    std::list<Expression *> args;

public:
    DynamicCallExpression(Expression *body, const std::list<Expression *> &args);
    ~DynamicCallExpression();

    Object *exec(Context *context);
};

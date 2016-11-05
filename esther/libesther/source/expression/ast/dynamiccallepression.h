#pragma once

#include "expression.h"

class DynamicCallEpression : public Expression {
    Expression *body;
    std::list<Expression *> args;

public:
    DynamicCallEpression(Expression *body, const std::list<Expression *> &args);
    ~DynamicCallEpression();

    Object *exec(Context *context);
};

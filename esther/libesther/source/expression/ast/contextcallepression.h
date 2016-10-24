#pragma once

#include "expression.h"

class ContextCallEpression : public Expression {
    Expression *self, *body;
    std::list<Expression *> args;

public:
    ContextCallEpression(Expression *self, Expression *body, const std::list<Expression *> &args);
    ~ContextCallEpression();

    Object *exec(Context *context);
};

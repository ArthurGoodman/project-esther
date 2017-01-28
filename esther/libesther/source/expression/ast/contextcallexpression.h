#pragma once

#include "expression.h"

class ContextCallExpression : public Expression {
    Expression *self, *body;
    std::list<Expression *> args;

public:
    ContextCallExpression(Expression *self, Expression *body, const std::list<Expression *> &args);
    ~ContextCallExpression();

    Object *exec(Esther *esther);
};

#pragma once

#include "expression.h"

class CallExpression : public Expression {
    Expression *f, *self;
    int args;

public:
    CallExpression(Expression *f, Expression *self, int args);
    ~CallExpression();

    Object *exec(Esther *esther);
};

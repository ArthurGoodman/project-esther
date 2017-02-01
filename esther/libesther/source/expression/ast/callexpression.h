#pragma once

#include "expression.h"

class CallExpression : public Expression {
    Expression *f, *self;
    int args;

public:
    CallExpression(Expression *f, Expression *self, int args);
    ~CallExpression();

    Pointer<Object> exec(Esther *esther) override;
};

#pragma once

#include "expression/expression.h"

class CallExpression : public Expression {
    Expression *f, *self;
    int args;

public:
    CallExpression(Expression *f, Expression *self, int args);
    ~CallExpression();

    Ptr<Object> exec(Esther *esther) override;
};

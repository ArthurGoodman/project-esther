#pragma once

#include "expression.h"

class OrExpression : public Expression {
    Expression *self, *arg;

public:
    OrExpression(Expression *self, Expression *arg);
    ~OrExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};

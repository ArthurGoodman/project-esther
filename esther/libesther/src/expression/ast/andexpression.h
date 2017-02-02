#pragma once

#include "expression/expression.h"

class AndExpression : public Expression {
    Expression *self, *arg;

public:
    AndExpression(Expression *self, Expression *arg);
    ~AndExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};

#pragma once

#include "expression/expression.h"

class NotExpression : public Expression {
    Expression *self;

public:
    NotExpression(Expression *self);
    ~NotExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};

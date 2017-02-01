#pragma once

#include "expression.h"

class NotExpression : public Expression {
    Expression *self;

public:
    NotExpression(Expression *self);
    ~NotExpression();

protected:
    Pointer<Object> exec(Esther *esther) override;
};

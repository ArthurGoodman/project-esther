#pragma once

#include "expression.h"

class NotExpression : public Expression {
    Expression *self;

public:
    NotExpression(Expression *self);
    ~NotExpression();

protected:
    Object *exec(Context *context);
};

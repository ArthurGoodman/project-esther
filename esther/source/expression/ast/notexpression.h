#pragma once

#include "expression.h"

class NotExpression : public Expression {
    Expression *self;

public:
    NotExpression(Expression *self);
    ~NotExpression();

    Object *exec(Context *context);
};

#pragma once
#include "common.h"

#include "expression.h"

class PostIncrementExpression : public Expression {
    Expression *self;

public:
    PostIncrementExpression(Expression *self);

    IObject *exec(Context *context);
};

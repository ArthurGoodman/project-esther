#pragma once
#include "common.h"

#include "expression.h"

class PostIncrementExpression : public Expression {
    Expression *self;

public:
    PostIncrementExpression(Expression *self);

    Object *eval(Context *context);
};

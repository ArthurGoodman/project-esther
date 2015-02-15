#pragma once
#include "common.h"

#include "expression.h"

class PostIncrementExpression : public Expression {
    Expression *self;

public:
    PostIncrementExpression(Expression *self);
    ~PostIncrementExpression();

    Object *eval(Context *context);
};

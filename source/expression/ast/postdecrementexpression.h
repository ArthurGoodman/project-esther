#pragma once
#include "common.h"

#include "expression.h"

class PostDecrementExpression : public Expression {
    Expression *self;

public:
    PostDecrementExpression(Expression *self);

    Object *eval(Context *context);
};

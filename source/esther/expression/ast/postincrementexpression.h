#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class PostIncrementExpression : public Expression {
    Expression *self;

public:
    PostIncrementExpression(Expression *self);
    ~PostIncrementExpression();

    Object *eval(Context *context);
};
}

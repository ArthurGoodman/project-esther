#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class PostDecrementExpression : public Expression {
    Expression *self;

public:
    PostDecrementExpression(Expression *self);
    ~PostDecrementExpression();

    Object *eval(Context *context);
};
}

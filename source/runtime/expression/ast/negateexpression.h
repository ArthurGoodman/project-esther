#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class NegateExpression : public Expression {
    Expression *self;

public:
    NegateExpression(Expression *self);
    ~NegateExpression();

    Object *eval(Context *context);
};
}

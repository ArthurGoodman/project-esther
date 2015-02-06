#pragma once
#include "common.h"

#include "expression.h"

namespace esther {

class BreakExpression : public Expression {
    Expression *value;

public:
    BreakExpression(Expression *value = 0);
    ~BreakExpression();

    Object *eval(Context *context);
};
}

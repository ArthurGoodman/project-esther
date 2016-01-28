#pragma once
#include "common.h"

#include "expression.h"

class BreakExpression : public Expression {
    Expression *value;

public:
    BreakExpression(Expression *value = 0);

    IObject *exec(Context *context);
};

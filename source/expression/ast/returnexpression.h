#pragma once

#include "expression.h"

class ReturnExpression : public Expression {
    Expression *value;

public:
    ReturnExpression(Expression *value = 0);

    IObject *exec(Context *context);
};

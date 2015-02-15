#pragma once
#include "common.h"

#include "expression.h"

class ReturnExpression : public Expression {
    Expression *value;

public:
    ReturnExpression(Expression *value = 0);

    Object *eval(Context *context);
};

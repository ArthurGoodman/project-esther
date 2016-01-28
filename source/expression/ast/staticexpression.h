#pragma once
#include "common.h"

#include "expression.h"

class StaticExpression : public Expression {
    Expression *body;

public:
    StaticExpression(Expression *body);

    IObject *exec(Context *context);
};

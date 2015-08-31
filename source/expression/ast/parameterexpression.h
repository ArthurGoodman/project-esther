#pragma once
#include "common.h"

#include "expression.h"

class ParameterExpression : public Expression {
    Expression *type, *name, *value;

public:
    ParameterExpression(Expression *type, Expression *name, Expression *value);

    Object *exec(Context *context);
};

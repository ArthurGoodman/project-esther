#pragma once
#include "common.h"

#include "expression.h"

class ParameterExpression : public Expression {
    Expression *type, *name, *value;
    bool dynamic;

public:
    ParameterExpression(Expression *type, Expression *name, Expression *value, bool dynamic);

    Object *exec(Context *context);
};

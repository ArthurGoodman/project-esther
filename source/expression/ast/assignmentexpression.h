#pragma once
#include "common.h"

#include "expression.h"

class AssignmentExpression : public Expression {
    Expression *expression, *value;

public:
    AssignmentExpression(Expression *expression, Expression *value);

    Object *exec(Context *context);
};

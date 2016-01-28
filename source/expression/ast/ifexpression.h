#pragma once
#include "common.h"

#include "expression.h"

class IfExpression : public Expression {
    Expression *condition, *body, *elseBody;

public:
    IfExpression(Expression *condition, Expression *body, Expression *elseBody);

    IObject *exec(Context *context);
};

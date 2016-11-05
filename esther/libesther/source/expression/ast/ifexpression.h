#pragma once

#include "expression.h"

class IfExpression : public Expression {
    Expression *condition, *body, *elseBody;

public:
    IfExpression(Expression *condition, Expression *body, Expression *elseBody);
    ~IfExpression();

    Object *exec(Context *context);
};
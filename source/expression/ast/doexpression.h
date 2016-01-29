#pragma once

#include "expression.h"

class DoExpression : public Expression {
    Expression *body, *condition;

public:
    DoExpression(Expression *body, Expression *condition);

    IObject *exec(Context *context);
};

#pragma once

#include "expression.h"

class ForExpression : public Expression {
    Expression * param;
    Expression *expression;
    Expression *body;

public:
    ForExpression(Expression *param, Expression *expression, Expression *body);

    IObject *exec(Context *context);
};

#pragma once
#include "common.h"

#include "expression.h"

class ForExpression : public Expression {
    Expression * param;
    Expression *expression;
    Expression *body;

public:
    ForExpression(Expression *param, Expression *expression, Expression *body);

    Object *exec(Context *context);
};

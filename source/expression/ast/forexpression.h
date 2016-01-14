#pragma once
#include "common.h"

#include "expression.h"

class ForExpression : public Expression {
    list<Expression *> params;
    Expression *expression;
    Expression *body;

public:
    ForExpression(list<Expression *> params, Expression *expression, Expression *body);

    Object *exec(Context *context);
};

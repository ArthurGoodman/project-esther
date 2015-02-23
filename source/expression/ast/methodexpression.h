#pragma once
#include "common.h"

#include "expression.h"

class MethodExpression : public Expression {
    Expression *type, *name;
    list<Expression *> params;
    Expression *body;

public:
    MethodExpression(Expression *type, Expression *name, list<Expression *> params, Expression *body);

    Object *eval(Context *context);
};

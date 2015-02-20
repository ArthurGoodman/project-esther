#pragma once
#include "common.h"

#include "expression.h"

class FunctionExpression : public Expression {
    Expression *type, *name;
    list<Expression *> params;
    Expression *body;

public:
    FunctionExpression(Expression *type, Expression *name, list<Expression *> params, Expression *body);

    Object *eval(Context *context);
};

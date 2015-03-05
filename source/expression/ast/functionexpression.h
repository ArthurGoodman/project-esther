#pragma once
#include "common.h"

#include "expression.h"

class FunctionExpression : public Expression {
    Expression *type, *name;
    list<Expression *> params;
    Expression *body;
    bool variadic;

public:
    FunctionExpression(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic);

    Object *eval(Context *context);
};

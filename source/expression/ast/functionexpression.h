#pragma once
#include "common.h"

#include "expression.h"

class FunctionExpression : public Expression {
    Expression *type, *name;
    list<Expression *> params;
    Expression *body;
    bool variadic, dynamic;

public:
    FunctionExpression(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic, bool dynamic);

    Object *exec(Context *context);
};

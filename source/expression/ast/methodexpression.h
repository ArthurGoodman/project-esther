#pragma once
#include "common.h"

#include "expression.h"

class MethodExpression : public Expression {
    Expression *type, *name;
    list<Expression *> params;
    Expression *body;
    bool variadic, dynamic;

public:
    MethodExpression(Expression *type, Expression *name, list<Expression *> params, Expression *body, bool variadic, bool dynamic);

    Object *exec(Context *context);
};

#pragma once

#include "expression.h"

class MethodExpression : public Expression {
    Expression *type, *name;
    std::list<Expression *> params;
    Expression *body;
    bool variadic, dynamic;

public:
    MethodExpression(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic);

    IObject *exec(Context *context);
};

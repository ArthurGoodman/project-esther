#pragma once

#include "expression.h"

class FunctionExpression : public Expression {
    Expression *type, *name;
    std::list<Expression *> params;
    Expression *body;
    bool variadic, dynamic;

public:
    FunctionExpression(Expression *type, Expression *name, std::list<Expression *> params, Expression *body, bool variadic, bool dynamic);

    IObject *exec(Context *context);
};

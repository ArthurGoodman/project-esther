#pragma once

#include "expression.h"

class ContextResolutionExpression : public Expression {
    Expression *self, *body;

public:
    ContextResolutionExpression(Expression *self, Expression *body);

    IObject *exec(Context *context);
};

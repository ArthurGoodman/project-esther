#pragma once

#include "expression.h"

class ContextResolutionExpression : public Expression {
    Expression *self, *body;

public:
    ContextResolutionExpression(Expression *self, Expression *body);
    ~ContextResolutionExpression();

    Object *exec(Context *context);
};

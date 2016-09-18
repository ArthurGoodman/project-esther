#pragma once

#include "expression.h"

class ContextResolutionExpression : public Expression {
    Expression *self, *body;
    Context *context;

public:
    ContextResolutionExpression(Expression *self, Expression *body, Context *context);
    ~ContextResolutionExpression();

    Object *exec(Context *context);
};

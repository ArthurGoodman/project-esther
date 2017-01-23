#pragma once

#include "expression.h"

class ContextResolutionExpression : public Expression {
    Expression *self, *body;
    bool object;

public:
    ContextResolutionExpression(Expression *self, Expression *body, bool object);
    ~ContextResolutionExpression();

protected:
    Object *exec(Context *context);
};

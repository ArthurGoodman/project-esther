#pragma once

#include "expression.h"

class ContextResolutionExpression : public Expression {
    Expression *self, *here, *body;

public:
    ContextResolutionExpression(Expression *self, Expression *here, Expression *body);
    ~ContextResolutionExpression();

protected:
    Object *exec(Esther *esther);
};

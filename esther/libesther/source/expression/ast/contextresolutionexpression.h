#pragma once

#include "expression.h"

class ContextResolutionExpression : public Expression {
    Expression *self, *body, *here;

public:
    ContextResolutionExpression(Expression *self, Expression *body, Expression *here);
    ~ContextResolutionExpression();

protected:
    Pointer<Object> exec(Esther *esther);
};

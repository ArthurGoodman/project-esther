#pragma once

#include "expression.h"

class LoopExpression : public Expression {
    Expression *condition, *body;

public:
    LoopExpression(Expression *condition, Expression *body);
    ~LoopExpression();

protected:
    Object *exec(Context *context);
};

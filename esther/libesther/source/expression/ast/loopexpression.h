#pragma once

#include "expression.h"

class LoopExpression : public Expression {
    Expression *condition, *body;

public:
    LoopExpression(Expression *condition, Expression *body);
    ~LoopExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};

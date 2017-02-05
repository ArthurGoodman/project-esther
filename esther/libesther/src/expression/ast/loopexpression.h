#pragma once

#include "expression/expression.h"

namespace es {

class LoopExpression : public Expression {
    Expression *condition, *body;

public:
    LoopExpression(Expression *condition, Expression *body);
    ~LoopExpression();

protected:
    Object *exec(Esther *esther) override;
};
}

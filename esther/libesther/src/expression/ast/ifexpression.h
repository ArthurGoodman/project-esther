#pragma once

#include "expression/expression.h"

namespace es {

class IfExpression : public Expression {
    Expression *condition, *body, *elseBody;

public:
    IfExpression(Expression *condition, Expression *body, Expression *elseBody);
    ~IfExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
}

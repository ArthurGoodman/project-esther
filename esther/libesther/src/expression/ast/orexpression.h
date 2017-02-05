#pragma once

#include "expression/expression.h"

namespace es {

class OrExpression : public Expression {
    Expression *self, *arg;

public:
    OrExpression(Expression *self, Expression *arg);
    ~OrExpression();

protected:
    Object *exec(Esther *esther) override;
};
}

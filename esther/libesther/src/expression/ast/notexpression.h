#pragma once

#include "expression/expression.h"

namespace es {

class NotExpression : public Expression {
    Expression *self;

public:
    NotExpression(Expression *self);
    ~NotExpression();

protected:
    Ptr<Object> exec(Esther *esther) override;
};
}

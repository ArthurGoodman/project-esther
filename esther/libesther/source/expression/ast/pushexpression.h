#pragma once

#include "expression.h"

class PushExpression : public Expression {
    Expression *arg;

public:
    PushExpression(Expression *arg);

protected:
    Ptr<Object> exec(Esther *esther) override;
};

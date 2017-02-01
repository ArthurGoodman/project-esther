#pragma once

#include "expression.h"

class PushExpression : public Expression {
    Expression *arg;

public:
    PushExpression(Expression *arg);

protected:
    Pointer<Object> exec(Esther *esther) override;
};

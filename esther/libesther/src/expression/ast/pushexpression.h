#pragma once

#include "expression/expression.h"

namespace es {

class PushExpression : public Expression {
    Expression *arg;

public:
    PushExpression(Expression *arg);

protected:
    Ptr<Object> exec(Esther *esther) override;
};
}

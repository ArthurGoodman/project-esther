#pragma once

#include "expression/expression.h"
#include "memory/pointer.h"

namespace es {

class ConstantExpression : public Expression {
    Ptr<Object> value;

public:
    ConstantExpression(Ptr<Object> value);

protected:
    Ptr<Object> exec(Esther *esther) override;
};
}

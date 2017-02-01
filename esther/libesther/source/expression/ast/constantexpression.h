#pragma once

#include "expression.h"

class ConstantExpression : public Expression {
    Pointer<Object> value;

public:
    ConstantExpression(Pointer<Object> value);

protected:
    Pointer<Object> exec(Esther *esther) override;
};

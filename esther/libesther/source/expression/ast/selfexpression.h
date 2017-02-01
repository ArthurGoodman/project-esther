#pragma once

#include "expression.h"

class SelfExpression : public Expression {
protected:
    Pointer<Object> exec(Esther *esther) override;
};

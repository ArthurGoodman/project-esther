#pragma once

#include "expression.h"

class EmptyExpression : public Expression {
protected:
    Pointer<Object> exec(Esther *esther) override;
};

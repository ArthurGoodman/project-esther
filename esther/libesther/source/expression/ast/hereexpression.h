#pragma once

#include "expression.h"

class HereExpression : public Expression {
protected:
    Pointer<Object> exec(Esther *esther) override;
};

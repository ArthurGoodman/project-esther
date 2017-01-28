#pragma once

#include "expression.h"

class ConstantExpression : public Expression {
    Object *value;

public:
    ConstantExpression(Object *value);

protected:
    Object *exec(Esther *esther);
};

#pragma once

#include "expression.h"

class ConstantExpression : public Expression {
    IObject *value;

public:
    ConstantExpression(IObject *value);

    IObject *exec(Context *context);
};

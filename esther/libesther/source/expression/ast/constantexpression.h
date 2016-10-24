#pragma once

#include "expression.h"

class ConstantExpression : public Expression {
    Object *value;

public:
    ConstantExpression(Object *value);

    Object *exec(Context *context);
};

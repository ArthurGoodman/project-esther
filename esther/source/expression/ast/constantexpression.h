#pragma once

#include "expression.h"

class ConstantExpression : public Expression {
public:
    Object *exec(Context *context);
};

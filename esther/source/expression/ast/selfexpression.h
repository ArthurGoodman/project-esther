#pragma once

#include "expression.h"

class SelfExpression : public Expression {
public:
    Object *exec(Context *context);
};

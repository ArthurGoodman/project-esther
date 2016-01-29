#pragma once

#include "expression.h"

class SelfExpression : public Expression {
public:
    IObject *exec(Context *context);
};

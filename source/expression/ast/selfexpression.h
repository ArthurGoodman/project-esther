#pragma once
#include "common.h"

#include "expression.h"

class SelfExpression : public Expression {
public:
    IObject *exec(Context *context);
};

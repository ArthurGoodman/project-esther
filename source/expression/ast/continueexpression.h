#pragma once
#include "common.h"

#include "expression.h"

class ContinueExpression : public Expression {
public:
    IObject *exec(Context *context);
};

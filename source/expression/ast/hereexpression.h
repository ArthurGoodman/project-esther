#pragma once
#include "common.h"

#include "expression.h"

class HereExpression : public Expression {
public:
    IObject *exec(Context *context);
};

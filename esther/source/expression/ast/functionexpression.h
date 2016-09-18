#pragma once

#include "expression.h"

class FunctionExpression : public Expression {
public:
    Object *exec(Context *context);
};

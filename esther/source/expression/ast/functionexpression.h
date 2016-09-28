#pragma once

#include "expression.h"

#include "function.h"

class FunctionExpression : public Expression {
    ::Function *f;

public:
    FunctionExpression(::Function *f);

    Object *exec(Context *context);
};

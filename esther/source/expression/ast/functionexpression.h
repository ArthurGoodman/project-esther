#pragma once

#include "expression.h"

#include "interpretedfunction.h"

class FunctionExpression : public Expression {
    InterpretedFunction *f;

public:
    FunctionExpression(InterpretedFunction *f);

    Object *exec(Context *context);
};

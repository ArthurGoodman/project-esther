#pragma once

#include "expression.h"

#include "interpretedfunction.h"

class FunctionExpression : public Expression {
    InterpretedFunction *f;
    Expression *name;

public:
    FunctionExpression(InterpretedFunction *f, Expression *name);

    Object *exec(Context *context);
};

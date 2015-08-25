#pragma once
#include "common.h"

#include "expression.h"

class ConstantExpression : public Expression {
    Object *value;

public:
    ConstantExpression(Object *value);

    Object *eval(Context *context);
};

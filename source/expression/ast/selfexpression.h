#pragma once
#include "common.h"

#include "expression.h"

class SelfExpression : public Expression {
public:
    Object *eval(Context *context);
};

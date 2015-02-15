#pragma once
#include "common.h"

#include "expression.h"

class ContinueExpression : public Expression {
public:
    Object *eval(Context *context);
};

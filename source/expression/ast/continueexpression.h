#pragma once

#include "expression.h"

class ContinueExpression : public Expression {
public:
    IObject *exec(Context *context);
};

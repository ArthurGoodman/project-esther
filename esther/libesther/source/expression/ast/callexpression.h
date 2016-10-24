#pragma once

#include "expression.h"

class CallExpression : public Expression {
public:
    Object *exec(Context *context);
};

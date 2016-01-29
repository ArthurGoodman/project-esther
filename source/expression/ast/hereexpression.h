#pragma once

#include "expression.h"

class HereExpression : public Expression {
public:
    IObject *exec(Context *context);
};

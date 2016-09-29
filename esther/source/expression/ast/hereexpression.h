#pragma once

#include "expression.h"

class HereExpression : public Expression {
public:
    Object *exec(Context *context);
};

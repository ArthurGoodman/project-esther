#pragma once

#include "expression.h"

class OrExpression : public Expression {
public:
    Object *exec(Context *context);
};

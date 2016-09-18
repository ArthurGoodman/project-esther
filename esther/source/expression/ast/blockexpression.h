#pragma once

#include "expression.h"

class BlockExpression : public Expression {
public:
    Object *exec(Context *context);
};

#pragma once

#include "expression.h"

class LoopExpression : public Expression {
public:
    Object *exec(Context *context);
};

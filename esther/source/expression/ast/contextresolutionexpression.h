#pragma once

#include "expression.h"

class ContextResolutionExpression : public Expression {
public:
    Object *exec(Context *context);
};

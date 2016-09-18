#pragma once

#include "expression.h"

class AndExpression : public Expression {
public:
    Object *exec(Context *context);
};

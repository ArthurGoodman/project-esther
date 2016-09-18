#pragma once

#include "expression.h"

class IfExpression : public Expression {
public:
    Object *exec(Context *context);
};

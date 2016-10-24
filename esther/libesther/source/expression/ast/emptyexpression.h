#pragma once

#include "expression.h"

class EmptyExpression : public Expression {
public:
    Object *exec(Context *context);
};

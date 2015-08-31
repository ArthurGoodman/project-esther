#pragma once
#include "common.h"

#include "expression.h"

class EmptyExpression : public Expression {
public:
    Object *exec(Context *context);
};

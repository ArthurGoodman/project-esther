#pragma once
#include "common.h"

#include "expression.h"

class EmptyExpression : public Expression {
public:
    IObject *exec(Context *context);
};

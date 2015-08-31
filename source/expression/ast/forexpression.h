#pragma once
#include "common.h"

#include "expression.h"

class ForExpression : public Expression {
public:
    ForExpression();

    Object *exec(Context *context);
};

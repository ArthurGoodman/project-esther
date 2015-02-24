#pragma once
#include "common.h"

#include "expression.h"

class ForExpression : public Expression {
public:
    ForExpression();

    Object *eval(Context *context);
};

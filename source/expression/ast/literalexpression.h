#pragma once
#include "common.h"

#include "expression.h"
#include "variant.h"

class LiteralExpression : public Expression {
    Variant value;

public:
    LiteralExpression(const Variant &value);

    IObject *exec(Context *context);
};

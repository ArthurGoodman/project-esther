#pragma once

#include "expression.h"
#include "variant.h"

class LiteralExpression : public Expression {
    Variant value;

public:
    LiteralExpression(const Variant &value);

    Object *exec(Context *context);
};
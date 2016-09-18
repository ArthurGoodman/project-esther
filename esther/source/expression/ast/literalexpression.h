#pragma once

#include "expression.h"

class LiteralExpression : public Expression {
public:
    Object *exec(Context *context);
};

#pragma once

#include "expression.h"

class IdentifierExpression : public Expression {
public:
    Object *exec(Context *context);
};

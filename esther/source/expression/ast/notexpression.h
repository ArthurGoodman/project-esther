#pragma once

#include "expression.h"

class NotExpression : public Expression {
public:
    Object *exec(Context *context);
};

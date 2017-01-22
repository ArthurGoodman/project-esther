#pragma once

#include "expression.h"

class SelfExpression : public Expression {
protected:
    Object *exec(Context *context);
};

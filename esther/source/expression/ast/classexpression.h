#pragma once

#include "expression.h"

class ClassExpression : public Expression {
public:
    Object *exec(Context *context);
};

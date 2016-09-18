#pragma once

#include "expression.h"

class AttributeAssignmentExpression : public Expression {
public:
    Object *exec(Context *context);
};

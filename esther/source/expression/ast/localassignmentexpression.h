#pragma once

#include "expression.h"

class LocalAssignmentExpression : public Expression {
public:
    Object *exec(Context *context);
};

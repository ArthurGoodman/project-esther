#pragma once

#include "expression.h"

class LocalAssignmentExpression : public Expression {
    Expression *name, *value;

public:
    LocalAssignmentExpression(Expression *name, Expression *value);
    ~LocalAssignmentExpression();

    Object *exec(Context *context);
};

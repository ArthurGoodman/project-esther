#pragma once

#include "expression.h"

class AttributeAssignmentExpression : public Expression {
    Expression *name, *value;

public:
    AttributeAssignmentExpression(Expression *name, Expression *value);
    ~AttributeAssignmentExpression();

    Object *exec(Context *context);
};

#pragma once

#include "expression.h"

class AttributeAssignmentExpression : public Expression {
    Expression *self, *name, *value;

public:
    AttributeAssignmentExpression(Expression *self, Expression *name, Expression *value);
    ~AttributeAssignmentExpression();

    Object *exec(Context *context);
};

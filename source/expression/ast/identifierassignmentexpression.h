#pragma once
#include "common.h"

#include "identifierexpression.h"

class IdentifierAssignmentExpression : public IdentifierExpression {
protected:
    Expression *value;

public:
    IdentifierAssignmentExpression(Expression *name, Expression *value);

    Object *exec(Context *context);
};

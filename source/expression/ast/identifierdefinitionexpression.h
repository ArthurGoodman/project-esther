#pragma once
#include "common.h"

#include "identifierassignmentexpression.h"

class IdentifierDefinitionExpression : public IdentifierAssignmentExpression {
    Expression *type;

public:
    IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value, bool dynamic);

    Object *exec(Context *context);
};

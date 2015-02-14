#pragma once
#include "common.h"

#include "identifierassignmentexpression.h"

namespace esther {

class IdentifierDefinitionExpression : public IdentifierAssignmentExpression {
    Expression *type;

public:
    IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value);
    ~IdentifierDefinitionExpression();

    Object *eval(Context *context);
};
}

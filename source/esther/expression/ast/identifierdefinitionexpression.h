#pragma once
#include "common.h"

#include "identifierassignmentexpression.h"

namespace esther {

class IdentifierDefinitionExpression : public IdentifierAssignmentExpression {
public:
    IdentifierDefinitionExpression(Expression *name, Expression *value);
    ~IdentifierDefinitionExpression();

    Object *eval(Context *context);
};
}

#pragma once
#include <common.h>

#include "identifierexpression.h"

namespace esther {

class IdentifierAssignmentExpression : public IdentifierExpression {
protected:
    Expression *value;

public:
    IdentifierAssignmentExpression(Expression *name, Expression *value);
    ~IdentifierAssignmentExpression();

    Object *eval(Context *context);
};
}

#pragma once
#include <common.h>

#include "expression.h"

namespace esther {

class IdentifierAssignmentExpression : public Expression {
    Expression *name, *value;

public:
    IdentifierAssignmentExpression(Expression *name, Expression *value);

    Object *eval(Context *context);
};
}

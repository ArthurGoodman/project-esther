#include "identifierassignmentexpression.h"

#include "esther.h"

namespace esther {

IdentifierAssignmentExpression::IdentifierAssignmentExpression(Expression *name, Expression *value)
    : IdentifierExpression(name), value(value) {
}

Object *IdentifierAssignmentExpression::eval(Context *context) {
    return Esther::getNull();
}
}

#include "identifierdefinitionexpression.h"

#include "esther.h"

namespace esther {

IdentifierDefinitionExpression::IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value)
    : IdentifierAssignmentExpression(name, value), type(type) {
}

Object *IdentifierDefinitionExpression::eval(Context *context) {
    return Esther::getNull();
}
}

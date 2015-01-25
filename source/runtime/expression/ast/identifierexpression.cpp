#include "identifierexpression.h"

#include "esther.h"

namespace esther {

IdentifierExpression::IdentifierExpression(Expression *name)
    : name(name) {
}

Object *IdentifierExpression::eval(Context *context) {
    return Esther::getNull();
}
}

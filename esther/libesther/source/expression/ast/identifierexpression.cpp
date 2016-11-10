#include "identifierexpression.h"

#include "context.h"
#include "runtime.h"

IdentifierExpression::IdentifierExpression(const std::string &name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
}

Object *IdentifierExpression::exec(Context *context) {
    Object *value = context->get(name);

    if (!value)
        Runtime::runtimeError("undefined identifier '" + name + "'");

    return value;
}

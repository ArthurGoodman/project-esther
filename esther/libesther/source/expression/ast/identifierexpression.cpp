#include "identifierexpression.h"

#include "context.h"
#include "esther.h"

IdentifierExpression::IdentifierExpression(const std::string &name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
}

Object *IdentifierExpression::exec(Context *context) {
    Object *value = context->get(name);

    if (value == nullptr)
        Esther::runtimeError("undefined identifier '" + name + "'");

    return value;
}

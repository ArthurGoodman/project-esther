#include "identifierexpression.h"

#include "context.h"
#include "esther.h"

IdentifierExpression::IdentifierExpression(const std::string &name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
}

Object *IdentifierExpression::exec(Esther *esther) {
    Object *value = esther->getContext()->get(name);

    if (value == nullptr)
        Esther::runtimeError("undefined identifier '" + name + "'");

    return value;
}

#include "identifierexpression.h"

#include "context.h"
#include "esther.h"

IdentifierExpression::IdentifierExpression(const std::string &name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
}

Object *IdentifierExpression::exec(Esther *esther) {
    Object *value = esther->context()->get(name);

    if (value == nullptr)
        Esther::runtimeError("IdentifierExpression:exec: undefined identifier '" + name + "'");

    return value;
}

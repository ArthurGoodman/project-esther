#include "identifierexpression.h"

#include "context.h"
#include "esther.h"

IdentifierExpression::IdentifierExpression(const std::string &name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
}

Pointer<Object> IdentifierExpression::exec(Esther *esther) {
    Pointer<Object> value = esther->context()->get(name);

    if (value == nullptr)
        Esther::runtimeError("IdentifierExpression:exec: undefined identifier '" + name + "'");

    return value;
}

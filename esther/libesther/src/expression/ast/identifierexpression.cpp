#include "identifierexpression.h"

#include "runtime/context.h"
#include "runtime/esther.h"

IdentifierExpression::IdentifierExpression(const std::string &name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
}

Ptr<Object> IdentifierExpression::exec(Esther *esther) {
    Ptr<Object> value = esther->context()->get(esther, name);

    if (value == nullptr)
        Esther::runtimeError("IdentifierExpression:exec: undefined identifier '" + name + "'");

    return value;
}
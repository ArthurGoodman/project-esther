#include "expression/ast/identifierexpression.h"

#include "runtime/context.h"
#include "esther.h"

namespace es {

IdentifierExpression::IdentifierExpression(const std::string &name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
}

Object *IdentifierExpression::exec(Esther *esther) {
    Object *value = esther->context()->get(esther, name);

    if (value == nullptr)
        Esther::runtimeError("IdentifierExpression:exec: undefined identifier '%s'", name.c_str());

    return value;
}
}

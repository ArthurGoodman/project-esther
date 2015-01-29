#include "identifierexpression.h"

#include "esther.h"
#include "context.h"

namespace esther {

IdentifierExpression::IdentifierExpression(Expression *name)
    : name(name) {
}

Object *IdentifierExpression::eval(Context *context) {
    string name = this->name->eval(context)->toString();

    if (!context->hasId(name))
        Esther::runtimeError("undefined identifier '" + name + "'");

    return context->getId(name);
}
}

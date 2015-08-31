#include "identifierexpression.h"

#include "runtime.h"
#include "context.h"

IdentifierExpression::IdentifierExpression(Expression *name)
    : name(name) {
}

Object *IdentifierExpression::exec(Context *context) {
    string name = this->name->eval(context)->toString();

    if (!context->hasId(name))
        Runtime::runtimeError("undefined identifier '" + name + "'");

    return context->getId(name);
}

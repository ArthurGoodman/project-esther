#include "identifierexpression.h"

#include "runtime.h"
#include "context.h"

namespace esther {

IdentifierExpression::IdentifierExpression(Expression *name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
    delete name;
}

Object *IdentifierExpression::eval(Context *context) {
    string name = this->name->eval(context)->toString();

    if (!context->hasId(name))
        Runtime::runtimeError("undefined identifier '" + name + "'");

    return context->getId(name);
}
}

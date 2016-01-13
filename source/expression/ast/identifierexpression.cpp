#include "identifierexpression.h"

#include "runtime.h"
#include "context.h"

IdentifierExpression::IdentifierExpression(Expression *name, bool dynamic)
    : name(name), dynamic(dynamic) {
}

Object *IdentifierExpression::exec(Context *context) {
    string name = dynamic ? this->name->eval(context)->toString() : this->name->eval(context)->immediateToString();

    if (!context->hasId(name))
        Runtime::runtimeError("undefined identifier '" + name + "'");

    return context->getId(name);
}

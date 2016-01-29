#include "identifierexpression.h"

#include "runtime.h"
#include "context.h"

IdentifierExpression::IdentifierExpression(Expression *name, bool dynamic)
    : name(name), dynamic(dynamic) {
}

Expression *IdentifierExpression::getName() {
    return name;
}

bool IdentifierExpression::isDynamic() {
    return dynamic;
}

IObject *IdentifierExpression::exec(Context *context) {
    std::string name = dynamic ? this->name->eval(context)->callToString() : this->name->eval(context)->toString();

    if (!context->hasId(name))
        Runtime::runtimeError("undefined identifier '" + name + "'");

    return context->getId(name);
}

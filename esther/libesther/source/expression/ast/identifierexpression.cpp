#include "identifierexpression.h"

#include "context.h"
#include "runtime.h"

IdentifierExpression::IdentifierExpression(Expression *name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
    delete name;
}

Object *IdentifierExpression::exec(Context *context) {
    const std::string &name = this->name->eval(context)->toString();
    Object *value = context->get(name);

    if (!value)
        Runtime::runtimeError("undefined identifier '" + name + "'");

    return value;
}

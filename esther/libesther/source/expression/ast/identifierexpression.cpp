#include "identifierexpression.h"

#include "context.h"

IdentifierExpression::IdentifierExpression(Expression *name)
    : name(name) {
}

IdentifierExpression::~IdentifierExpression() {
    delete name;
}

Object *IdentifierExpression::exec(Context *context) {
    return context->get(name->eval(context)->toString());
}

#include "identifierassignmentexpression.h"

#include "esther.h"
#include "context.h"

namespace esther {

IdentifierAssignmentExpression::IdentifierAssignmentExpression(Expression *name, Expression *value)
    : IdentifierExpression(name), value(value) {
}

Object *IdentifierAssignmentExpression::eval(Context *context) {
    string name = this->name->eval(context)->toString();
    Object *value = this->value->eval(context);

    if (!context->setId(name, value) || context->isObjectContext())
        context->setLocal(name, value);

    return value;
}
}

#include "identifierdefinitionexpression.h"

#include "esther.h"
#include "class.h"
#include "context.h"

namespace esther {

IdentifierDefinitionExpression::IdentifierDefinitionExpression(Expression *name, Expression *value)
    : IdentifierAssignmentExpression(name, value) {
}

IdentifierDefinitionExpression::~IdentifierDefinitionExpression() {
    delete name;
    delete value;
}

Object *IdentifierDefinitionExpression::eval(Context *context) {
    string name = this->name->eval(context)->toString();
    Object *value = this->value ? this->value->eval(context) : new Object;

    context->setLocal(name, value);

    return value;
}
}

#include "identifierdefinitionexpression.h"

#include "esther.h"
#include "class.h"
#include "context.h"

IdentifierDefinitionExpression::IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value)
    : IdentifierAssignmentExpression(name, value), type(type) {
}

IdentifierDefinitionExpression::~IdentifierDefinitionExpression() {
    delete type;
}

Object *IdentifierDefinitionExpression::eval(Context *context) {
    string name = this->name->eval(context)->toString();
    Object *value = this->value ? this->value->eval(context) : new Object;

    context->setLocal(name, value);

    return value;
}

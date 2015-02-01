#include "identifierdefinitionexpression.h"

#include "esther.h"
#include "class.h"
#include "context.h"

namespace esther {

IdentifierDefinitionExpression::IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value)
    : IdentifierAssignmentExpression(name, value), type(type) {
}

IdentifierDefinitionExpression::~IdentifierDefinitionExpression() {
    delete type;
    delete name;
    delete value;
}

Object *IdentifierDefinitionExpression::eval(Context *context) {
    string name = this->name->eval(context)->toString();
    Object *value = this->value ? this->value->eval(context) : 0;

    if (type) {
        Class *type = (Class *)this->type->eval(context);

        if (!type->is(Esther::getRootClass("Class")))
            Esther::runtimeError("class expected");

        if (value) {
            if (!value->is(type))
                value = value->as(type);
        } else
            value = type->newInstance();
    }

    if (!value)
        value = new Object;

    context->setLocal(name, value);

    return value;
}
}

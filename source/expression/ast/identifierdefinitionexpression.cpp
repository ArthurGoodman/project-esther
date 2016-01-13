#include "identifierdefinitionexpression.h"

#include "runtime.h"
#include "esther.h"
#include "class.h"
#include "context.h"

IdentifierDefinitionExpression::IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value, bool dynamic)
    : IdentifierAssignmentExpression(name, value, dynamic), type(type) {
}

Object *IdentifierDefinitionExpression::exec(Context *context) {
    string name = dynamic ? this->name->eval(context)->toString() : this->name->eval(context)->immediateToString();
    Object *value = this->value ? this->value->eval(context) : 0;

    if (type) {
        Class *type = (Class *)this->type->eval(context);

        if (!type->is("Class"))
            Runtime::runtimeError("class expected");

        if (value)
            value = value->as(type);
        else
            value = type->newInstance();
    }

    if (!value)
        value = new Object;

    context->setLocal(name, value);

    return value;
}

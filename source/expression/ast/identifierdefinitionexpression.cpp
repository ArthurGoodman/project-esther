#include "identifierdefinitionexpression.h"

#include "runtime.h"
#include "esther.h"
#include "class.h"
#include "context.h"

IdentifierDefinitionExpression::IdentifierDefinitionExpression(Expression *type, Expression *name, Expression *value, bool dynamic)
    : IdentifierExpression(name, dynamic), type(type), value(value) {
}

void IdentifierDefinitionExpression::setValue(Expression *value) {
    this->value = value;
}

IObject *IdentifierDefinitionExpression::exec(Context *context) {
    std::string name = dynamic ? this->name->eval(context)->callToString() : this->name->eval(context)->toString();
    IObject *value = this->value ? this->value->eval(context) : 0;

    if (type) {
        Class *type = (Class *)this->type->eval(context);

        if (!type->is("Class")) {
            setPosition(this->type->getPosition());
            Runtime::runtimeError("class expected in identifier type");
        }

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

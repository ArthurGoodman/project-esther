#include "parameterexpression.h"

#include "runtime.h"
#include "class.h"
#include "parameter.h"

ParameterExpression::ParameterExpression(Expression *type, Expression *name, Expression *value, bool dynamic)
    : type(type), name(name), value(value), dynamic(dynamic) {
}

IObject *ParameterExpression::exec(Context *context) {
    Class *type = this->type ? (Class *)this->type->eval(context) : Runtime::getObjectClass();

    if (!type->is("Class")) {
        setPosition(this->type->getPosition());
        Runtime::runtimeError("class expected in parameter type");
    }

    string name = dynamic ? this->name->eval(context)->callToString() : this->name->eval(context)->toString();
    IObject *value = this->value ? this->value->eval(context)->as(type) : 0;

    return new Parameter(type, name, value);
}

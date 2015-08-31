#include "parameterexpression.h"

#include "runtime.h"
#include "class.h"
#include "parameter.h"

ParameterExpression::ParameterExpression(Expression *type, Expression *name, Expression *value)
    : type(type), name(name), value(value) {
}

Object *ParameterExpression::exec(Context *context) {
    Class *type = this->type ? (Class *)this->type->eval(context) : Runtime::getObjectClass();

    if (!type->is("Class"))
        Runtime::runtimeError("class expected");

    string name = this->name->eval(context)->toString();
    Object *value = this->value ? this->value->eval(context)->as(type) : 0;

    return new Parameter(type, name, value);
}

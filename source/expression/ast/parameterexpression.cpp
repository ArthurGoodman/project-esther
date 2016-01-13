#include "parameterexpression.h"

#include "runtime.h"
#include "class.h"
#include "parameter.h"

ParameterExpression::ParameterExpression(Expression *type, Expression *name, Expression *value, bool dynamic)
    : type(type), name(name), value(value), dynamic(dynamic) {
}

Object *ParameterExpression::exec(Context *context) {
    Class *type = this->type ? (Class *)this->type->eval(context) : Runtime::getObjectClass();

    if (!type->is("Class"))
        Runtime::runtimeError("class expected");

    string name = dynamic ? this->name->eval(context)->toString() : this->name->eval(context)->immediateToString();
    Object *value = this->value ? this->value->eval(context)->as(type) : 0;

    return new Parameter(type, name, value);
}

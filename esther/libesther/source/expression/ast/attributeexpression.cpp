#include "attributeexpression.h"

#include "context.h"
#include "runtime.h"

AttributeExpression::AttributeExpression(Expression *self, const std::string &name)
    : self(self)
    , name(name) {
}

AttributeExpression::~AttributeExpression() {
    delete self;
}

Object *AttributeExpression::exec(Context *context) {
    Object *value = self->eval(context)->get(name);

    if (value == nullptr)
        Runtime::runtimeError("undefined identifier '" + name + "'");

    return value;
}

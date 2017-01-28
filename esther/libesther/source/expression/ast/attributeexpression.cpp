#include "attributeexpression.h"

#include "context.h"
#include "esther.h"

AttributeExpression::AttributeExpression(Expression *self, const std::string &name)
    : self(self)
    , name(name) {
}

AttributeExpression::~AttributeExpression() {
    delete self;
}

Object *AttributeExpression::exec(Esther *esther) {
    Object *value = self->eval(esther)->get(name);

    if (value == nullptr)
        Esther::runtimeError("undefined identifier '" + name + "'");

    return value;
}

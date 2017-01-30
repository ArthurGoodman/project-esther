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

Pointer<Object> AttributeExpression::exec(Esther *esther) {
    Pointer<Object> value = self->eval(esther)->get(name);

    if (value == nullptr)
        Esther::runtimeError("undefined attribute '" + name + "'");

    return value;
}

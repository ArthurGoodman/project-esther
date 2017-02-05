#include "expression/ast/attributeexpression.h"

#include "runtime/object.h"
#include "runtime/context.h"
#include "esther.h"

namespace es {

AttributeExpression::AttributeExpression(Expression *self, const std::string &name)
    : self(self)
    , name(name) {
}

AttributeExpression::~AttributeExpression() {
    delete self;
}

Object *AttributeExpression::exec(Esther *esther) {
    Object *value = self->eval(esther)->get(name);

    if (!value)
        Esther::runtimeError("undefined attribute '" + name + "'");

    return value;
}
}

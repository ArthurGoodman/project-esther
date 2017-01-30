#include "attributeassignmentexpression.h"

#include "context.h"

AttributeAssignmentExpression::AttributeAssignmentExpression(Expression *self, const std::string &name, Expression *value)
    : self(self)
    , name(name)
    , value(value) {
}

AttributeAssignmentExpression::~AttributeAssignmentExpression() {
    delete self;
    delete value;
}

Pointer<Object> AttributeAssignmentExpression::exec(Esther *esther) {
    Pointer<Object> evaledSelf = self->eval(esther);
    Pointer<Object> evaledValue = value->eval(esther);

    evaledSelf->setAttribute(name, evaledValue);

    return evaledValue;
}

#include "attributeassignmentexpression.h"

#include "runtime/context.h"

AttributeAssignmentExpression::AttributeAssignmentExpression(Expression *self, const std::string &name, Expression *value)
    : self(self)
    , name(name)
    , value(value) {
}

AttributeAssignmentExpression::~AttributeAssignmentExpression() {
    delete self;
    delete value;
}

Ptr<Object> AttributeAssignmentExpression::exec(Esther *esther) {
    Ptr<Object> evaledSelf = self->eval(esther);
    Ptr<Object> evaledValue = value->eval(esther);

    evaledSelf->setAttribute(name, evaledValue);

    return evaledValue;
}

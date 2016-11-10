#include "attributeassignmentexpression.h"

#include "context.h"

AttributeAssignmentExpression::AttributeAssignmentExpression(Expression *self, const std::string &name, Expression *value)
    : self(self), name(name), value(value) {
}

AttributeAssignmentExpression::~AttributeAssignmentExpression() {
    delete self;
    delete value;
}

Object *AttributeAssignmentExpression::exec(Context *context) {
    Object *evaledSelf = self->eval(context);
    Object *evaledValue = value->eval(context);

    evaledSelf->setAttribute(name, evaledValue);

    return evaledValue;
}

#include "attributeassignmentexpression.h"

#include "context.h"

AttributeAssignmentExpression::AttributeAssignmentExpression(Expression *self, Expression *name, Expression *value)
    : self(self), name(name), value(value) {
}

AttributeAssignmentExpression::~AttributeAssignmentExpression() {
    delete self;
    delete name;
    delete value;
}

Object *AttributeAssignmentExpression::exec(Context *context) {
    Object *evaledSelf = self->eval(context);
    const std::string &evaledName = name->eval(context)->toString();
    Object *evaledValue = value->eval(context);

    evaledSelf->setAttribute(evaledName, evaledValue);

    return evaledValue;
}

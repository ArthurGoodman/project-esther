#include "attributeassignmentexpression.h"

#include "context.h"

AttributeAssignmentExpression::AttributeAssignmentExpression(Expression *name, Expression *value)
    : name(name), value(value) {
}

AttributeAssignmentExpression::~AttributeAssignmentExpression() {
    delete name;
    delete value;
}

Object *AttributeAssignmentExpression::exec(Context *context) {
    Object *value = this->value->eval(context);
    context->getSelf()->setAttribute(name->eval(context)->toString(), value);
    return value;
}

#include "localassignmentexpression.h"

#include "context.h"

LocalAssignmentExpression::LocalAssignmentExpression(Expression *name, Expression *value)
    : name(name), value(value) {
}

LocalAssignmentExpression::~LocalAssignmentExpression() {
    delete name;
    delete value;
}

Object *LocalAssignmentExpression::exec(Context *context) {
    Object *value = this->value->eval(context);
    context->setLocal(name->eval(context)->toString(), value);
    return value;
}

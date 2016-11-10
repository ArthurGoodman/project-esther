#include "localassignmentexpression.h"

#include "context.h"

LocalAssignmentExpression::LocalAssignmentExpression(const std::string &name, Expression *value)
    : name(name), value(value) {
}

LocalAssignmentExpression::~LocalAssignmentExpression() {
    delete value;
}

Object *LocalAssignmentExpression::exec(Context *context) {
    Object *value = this->value->eval(context);
    context->setLocal(name, value);
    return value;
}

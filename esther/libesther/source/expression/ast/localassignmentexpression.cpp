#include "localassignmentexpression.h"

#include "context.h"

LocalAssignmentExpression::LocalAssignmentExpression(const std::string &name, Expression *value)
    : name(name)
    , value(value) {
}

LocalAssignmentExpression::~LocalAssignmentExpression() {
    delete value;
}

Object *LocalAssignmentExpression::exec(Context *context) {
    Object *evaledValue = value->eval(context);
    context->setLocal(name, evaledValue);
    return evaledValue;
}

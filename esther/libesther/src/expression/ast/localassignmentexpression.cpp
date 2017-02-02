#include "localassignmentexpression.h"

#include "runtime/esther.h"
#include "runtime/context.h"

LocalAssignmentExpression::LocalAssignmentExpression(const std::string &name, Expression *value)
    : name(name)
    , value(value) {
}

LocalAssignmentExpression::~LocalAssignmentExpression() {
    delete value;
}

Ptr<Object> LocalAssignmentExpression::exec(Esther *esther) {
    Ptr<Object> evaledValue = value->eval(esther);
    esther->context()->setLocal(name, evaledValue);
    return evaledValue;
}

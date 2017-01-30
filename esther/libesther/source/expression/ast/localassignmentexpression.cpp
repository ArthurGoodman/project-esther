#include "localassignmentexpression.h"

#include "esther.h"
#include "context.h"

LocalAssignmentExpression::LocalAssignmentExpression(const std::string &name, Expression *value)
    : name(name)
    , value(value) {
}

LocalAssignmentExpression::~LocalAssignmentExpression() {
    delete value;
}

Pointer<Object> LocalAssignmentExpression::exec(Esther *esther) {
    Pointer<Object> evaledValue = value->eval(esther);
    esther->context()->setLocal(name, evaledValue);
    return evaledValue;
}

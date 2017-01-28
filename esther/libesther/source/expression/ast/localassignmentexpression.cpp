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

Object *LocalAssignmentExpression::exec(Esther *esther) {
    Object *evaledValue = value->eval(esther);
    esther->getContext()->setLocal(name, evaledValue);
    return evaledValue;
}

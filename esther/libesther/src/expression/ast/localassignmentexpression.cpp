#include "expression/ast/localassignmentexpression.h"

#include "esther.h"
#include "runtime/context.h"

namespace es {

LocalAssignmentExpression::LocalAssignmentExpression(const std::string &name, Expression *value)
    : name(name)
    , value(value) {
}

LocalAssignmentExpression::~LocalAssignmentExpression() {
    delete value;
}

Ptr<Object> LocalAssignmentExpression::exec(Esther *esther) {
    Ptr<Object> evaledValue = value->eval(esther);
    esther->context()->setLocal(esther, name, evaledValue);
    return evaledValue;
}
}

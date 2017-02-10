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

Object *LocalAssignmentExpression::exec(Esther *esther) {
    Object *volatile evaledValue = value->eval(esther);
    esther->context()->setLocal(name, evaledValue);
    return evaledValue;
}
}

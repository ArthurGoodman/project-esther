#include "expression/ast/assignmentexpression.h"

#include "esther.h"
#include "runtime/context.h"

namespace es {

AssignmentExpression::AssignmentExpression(const std::string &name, Expression *value)
    : name(name)
    , value(value) {
}

AssignmentExpression::~AssignmentExpression() {
    delete value;
}

Ptr<Object> AssignmentExpression::exec(Esther *esther) {
    Ptr<Object> evaledValue = value->eval(esther);

    if (!esther->context()->set(esther, name, evaledValue))
        esther->context()->setLocal(esther, name, evaledValue);

    return evaledValue;
}
}

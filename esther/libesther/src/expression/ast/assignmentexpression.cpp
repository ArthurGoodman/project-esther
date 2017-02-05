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

Object *AssignmentExpression::exec(Esther *esther) {
    Object *evaledValue = value->eval(esther);

    if (!esther->context()->set(name, evaledValue))
        esther->context()->setLocal(name, evaledValue);

    return evaledValue;
}
}

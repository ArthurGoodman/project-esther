#include "assignmentexpression.h"

#include "runtime/esther.h"
#include "runtime/context.h"

AssignmentExpression::AssignmentExpression(const std::string &name, Expression *value)
    : name(name)
    , value(value) {
}

AssignmentExpression::~AssignmentExpression() {
    delete value;
}

Ptr<Object> AssignmentExpression::exec(Esther *esther) {
    Ptr<Object> evaledValue = value->eval(esther);

    if (!esther->context()->set(name, evaledValue))
        esther->context()->setLocal(name, evaledValue);

    return evaledValue;
}

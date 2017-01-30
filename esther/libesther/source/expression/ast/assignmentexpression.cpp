#include "assignmentexpression.h"

#include "esther.h"
#include "context.h"

AssignmentExpression::AssignmentExpression(const std::string &name, Expression *value)
    : name(name)
    , value(value) {
}

AssignmentExpression::~AssignmentExpression() {
    delete value;
}

Pointer<Object> AssignmentExpression::exec(Esther *esther) {
    Pointer<Object> evaledValue = value->eval(esther);

    if (!esther->context()->set(name, evaledValue))
        esther->context()->setLocal(name, evaledValue);

    return evaledValue;
}

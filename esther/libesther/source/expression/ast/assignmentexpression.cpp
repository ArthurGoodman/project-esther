#include "assignmentexpression.h"

#include "context.h"

AssignmentExpression::AssignmentExpression(const std::string &name, Expression *value)
    : name(name)
    , value(value) {
}

AssignmentExpression::~AssignmentExpression() {
    delete value;
}

Object *AssignmentExpression::exec(Context *context) {
    Object *evaledValue = value->eval(context);

    if (!context->set(name, evaledValue))
        context->setLocal(name, evaledValue);

    return evaledValue;
}

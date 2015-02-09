#include "breakexpression.h"

#include "runtime.h"
#include "breakexception.h"

namespace esther {

BreakExpression::BreakExpression(Expression *value)
    : value(value) {
}

BreakExpression::~BreakExpression() {
    if (value)
        delete value;
}

Object *BreakExpression::eval(Context *context) {
    throw new BreakException(value ? value->eval(context) : Runtime::getNull());
}
}

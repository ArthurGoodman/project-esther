#include "breakexpression.h"

#include "runtime.h"
#include "breakexception.h"

BreakExpression::BreakExpression(Expression *value)
    : value(value) {
}

Object *BreakExpression::eval(Context *context) {
    throw new BreakException(value ? value->eval(context) : Runtime::getNull());
}

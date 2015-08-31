#include "breakexpression.h"

#include "runtime.h"
#include "breakexception.h"

BreakExpression::BreakExpression(Expression *value)
    : value(value) {
}

Object *BreakExpression::exec(Context *context) {
    throw new BreakException(value ? value->eval(context) : Runtime::getNull());
}

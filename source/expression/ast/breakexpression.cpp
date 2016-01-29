#include "breakexpression.h"

#include "runtime.h"
#include "breakexception.h"

BreakExpression::BreakExpression(Expression *value)
    : value(value) {
}

IObject *BreakExpression::exec(Context *context) {
    throw new BreakException(value ? value->eval(context) : Runtime::getNull());
}

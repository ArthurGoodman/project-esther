#include "breakexpression.h"

#include "esther.h"

namespace esther {

BreakExpression::BreakExpression(Expression *value)
    : value(value) {
}

Object *BreakExpression::eval(Context *context) {
    return Esther::getNull();
}
}

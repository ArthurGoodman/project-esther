#include "literalexpression.h"

namespace esther {

LiteralExpression::LiteralExpression(Object *value)
    : value(value) {
}

Object *LiteralExpression::eval(Context *) {
    return value;
}
}

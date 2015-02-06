#include "literalexpression.h"

#include "object.h"
#include "objectarray.h"

namespace esther {

LiteralExpression::LiteralExpression(Object *value)
    : value(value) {
}

Object *LiteralExpression::eval(Context *) {
    return value;
}
}

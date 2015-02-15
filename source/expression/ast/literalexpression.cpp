#include "literalexpression.h"

LiteralExpression::LiteralExpression(Object *value)
    : value(value) {
}

Object *LiteralExpression::eval(Context *) {
    return value;
}

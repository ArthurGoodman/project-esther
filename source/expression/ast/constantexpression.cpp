#include "constantexpression.h"

ConstantExpression::ConstantExpression(Object *value)
    : value(value) {
}

Object *ConstantExpression::eval(Context *) {
    return value;
}

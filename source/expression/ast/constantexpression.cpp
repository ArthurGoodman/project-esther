#include "constantexpression.h"

ConstantExpression::ConstantExpression(Object *value)
    : value(value) {
}

Object *ConstantExpression::exec(Context *) {
    return value;
}

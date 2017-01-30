#include "constantexpression.h"

ConstantExpression::ConstantExpression(Pointer<Object> value)
    : value(value) {
}

Pointer<Object> ConstantExpression::exec(Esther *) {
    return value;
}

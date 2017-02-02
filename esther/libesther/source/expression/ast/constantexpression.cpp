#include "constantexpression.h"

ConstantExpression::ConstantExpression(Ptr<Object> value)
    : value(value) {
}

Ptr<Object> ConstantExpression::exec(Esther *) {
    return value;
}

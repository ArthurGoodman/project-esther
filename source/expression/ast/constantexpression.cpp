#include "constantexpression.h"

ConstantExpression::ConstantExpression(IObject *value)
    : value(value) {
}

IObject *ConstantExpression::exec(Context *) {
    return value;
}

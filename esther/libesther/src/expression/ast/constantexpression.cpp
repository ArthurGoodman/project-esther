#include "expression/ast/constantexpression.h"

namespace es {

ConstantExpression::ConstantExpression(Object *volatile value)
    : value(value) {
}

Object *ConstantExpression::exec(Esther *) {
    return value;
}
}

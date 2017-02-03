#include "expression/ast/constantexpression.h"

namespace es {

ConstantExpression::ConstantExpression(Ptr<Object> value)
    : value(value) {
}

Ptr<Object> ConstantExpression::exec(Esther *) {
    return value;
}
}

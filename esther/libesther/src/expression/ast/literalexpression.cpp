#include "expression/ast/literalexpression.h"

#include "esther.h"
#include "runtime/context.h"
#include "runtime/valueobject.h"

namespace es {

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

Ptr<Object> LiteralExpression::exec(Esther *esther) {
    return new ValueObject(esther, value);
}
}

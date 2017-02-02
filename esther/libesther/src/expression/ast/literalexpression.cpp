#include "literalexpression.h"

#include "runtime/esther.h"
#include "runtime/context.h"
#include "runtime/valueobject.h"

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

Ptr<Object> LiteralExpression::exec(Esther *esther) {
    return new ValueObject(esther, value);
}

#include "literalexpression.h"

#include "esther.h"
#include "context.h"
#include "valueobject.h"

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

Ptr<Object> LiteralExpression::exec(Esther *esther) {
    return new ValueObject(esther, value);
}

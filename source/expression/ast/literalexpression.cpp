#include "literalexpression.h"

#include "valueobject.h"

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

Object *LiteralExpression::eval(Context *) {
    return new ValueObject(value);
}

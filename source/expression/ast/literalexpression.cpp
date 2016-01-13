#include "literalexpression.h"

#include "valueobject.h"

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

Object *LiteralExpression::exec(Context *) {
    return ValueObject::createNewInstance(value);
}

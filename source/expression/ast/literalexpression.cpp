#include "literalexpression.h"

#include "valueobject.h"

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

IObject *LiteralExpression::exec(Context *) {
    return ValueObject::createNewInstance(value);
}

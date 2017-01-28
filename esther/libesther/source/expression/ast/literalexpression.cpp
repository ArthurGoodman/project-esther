#include "literalexpression.h"

#include "esther.h"
#include "context.h"
#include "valueobject.h"

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

Object *LiteralExpression::exec(Esther *esther) {
    return esther->createValueObject(value);
}

#include "literalexpression.h"

#include "valueobject.h"
#include "context.h"

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

Object *LiteralExpression::exec(Context *context) {
    return ValueObject::createNewInstance(context->getRuntime(), value);
}

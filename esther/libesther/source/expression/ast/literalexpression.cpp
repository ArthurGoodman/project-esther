#include "literalexpression.h"

#include "runtime.h"
#include "context.h"
#include "valueobject.h"

LiteralExpression::LiteralExpression(const Variant &value)
    : value(value) {
}

Object *LiteralExpression::exec(Context *context) {
    return context->getRuntime()->createValueObject(value);
}

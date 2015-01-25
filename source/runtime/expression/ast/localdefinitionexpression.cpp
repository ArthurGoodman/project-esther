#include "localdefinitionexpression.h"

#include "esther.h"

namespace esther {

LocalDefinitionExpression::LocalDefinitionExpression(Expression *type, Expression *name, Expression *value)
    : type(type), name(name), value(value) {
}

Object *LocalDefinitionExpression::eval(Context *context) {
    return Esther::getNull();
}
}

#include "returnexpression.h"

#include "esther.h"

namespace esther {

ReturnExpression::ReturnExpression(Expression *value)
    : value(value) {
}

Object *ReturnExpression::eval(Context *context) {
    return Esther::getNull();
}
}

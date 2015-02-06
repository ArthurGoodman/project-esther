#include "returnexpression.h"

#include "runtime.h"
#include "returnexception.h"

namespace esther {

ReturnExpression::ReturnExpression(Expression *value)
    : value(value) {
}

ReturnExpression::~ReturnExpression() {
    if (value)
        delete value;
}

Object *ReturnExpression::eval(Context *context) {
    throw ReturnException(value ? value->eval(context) : Runtime::getNull());
}
}

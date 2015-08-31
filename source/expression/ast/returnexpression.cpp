#include "returnexpression.h"

#include "runtime.h"
#include "returnexception.h"

ReturnExpression::ReturnExpression(Expression *value)
    : value(value) {
}

Object *ReturnExpression::exec(Context *context) {
    throw new ReturnException(value ? value->eval(context) : Runtime::getNull());
}

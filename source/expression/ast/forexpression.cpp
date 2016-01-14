#include "forexpression.h"

#include "runtime.h"
#include "continueexception.h"
#include "breakexception.h"

ForExpression::ForExpression(list<Expression *> params, Expression *expression, Expression *body)
    : params(params), expression(expression), body(body) {
}

Object *ForExpression::exec(Context *context) {
    return Runtime::getNull();
}

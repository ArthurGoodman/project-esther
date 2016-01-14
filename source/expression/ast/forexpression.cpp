#include "forexpression.h"

#include "runtime.h"
#include "continueexception.h"
#include "breakexception.h"
#include "function.h"
#include "signature.h"
#include "interpretedblock.h"

ForExpression::ForExpression(list<Expression *> params, Expression *expression, Expression *body)
    : params(params), expression(expression), body(body) {
}

Object *ForExpression::exec(Context *context) {
    list<Parameter *> actualParams;

    for(Expression *param : params)
        actualParams << (Parameter *)param->eval(context);

    Function *f = new Function("", context, new Signature(Runtime::getObjectClass(), actualParams), new InterpretedBlock(body));
    expression->eval(context)->call("each", f);

    return Runtime::getNull();
}

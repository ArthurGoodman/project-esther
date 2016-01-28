#include "forexpression.h"

#include "runtime.h"
#include "continueexception.h"
#include "breakexception.h"
#include "function.h"
#include "signature.h"
#include "interpretedblock.h"

ForExpression::ForExpression(Expression *param, Expression *expression, Expression *body)
    : param(param), expression(expression), body(body) {
}

IObject *ForExpression::exec(Context *context) {
    Function *f = new Function("", context, new Signature(Runtime::getObjectClass(), list<Parameter *>(1, (Parameter *)param->eval(context))), new InterpretedBlock(body));
    expression->eval(context)->call("each", f);

    return Runtime::getNull();
}

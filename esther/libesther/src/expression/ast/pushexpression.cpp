#include "pushexpression.h"

#include "runtime/esther.h"

PushExpression::PushExpression(Expression *arg)
    : arg(arg) {
}

Ptr<Object> PushExpression::exec(Esther *esther) {
    Ptr<Object> evaledArg = arg->eval(esther);
    esther->push(evaledArg);
    return evaledArg;
}

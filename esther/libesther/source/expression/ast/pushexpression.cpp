#include "pushexpression.h"

#include "esther.h"

PushExpression::PushExpression(Expression *arg)
    : arg(arg) {
}

Pointer<Object> PushExpression::exec(Esther *esther) {
    Pointer<Object> evaledArg = arg->eval(esther);
    esther->push(evaledArg);
    return evaledArg;
}

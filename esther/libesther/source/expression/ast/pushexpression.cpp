#include "pushexpression.h"

#include "esther.h"

PushExpression::PushExpression(Expression *arg)
    : arg(arg) {
}

Object *PushExpression::exec(Esther *esther) {
    Object *evaledArg = arg->eval(esther);
    esther->push(evaledArg);
    return evaledArg;
}

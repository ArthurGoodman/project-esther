#include "expression/ast/pushexpression.h"

#include "esther.h"

namespace es {

PushExpression::PushExpression(Expression *arg)
    : arg(arg) {
}

Object *PushExpression::exec(Esther *esther) {
    Object *volatile evaledArg = arg->eval(esther);
    esther->push(evaledArg);
    return evaledArg;
}
}

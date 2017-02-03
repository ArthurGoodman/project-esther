#include "expression/ast/pushexpression.h"

#include "esther.h"

namespace es {

PushExpression::PushExpression(Expression *arg)
    : arg(arg) {
}

Ptr<Object> PushExpression::exec(Esther *esther) {
    Ptr<Object> evaledArg = arg->eval(esther);
    esther->push(evaledArg);
    return evaledArg;
}
}

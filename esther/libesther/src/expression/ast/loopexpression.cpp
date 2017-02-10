#include "expression/ast/loopexpression.h"

#include "runtime/object.h"
#include "runtime/context.h"
#include "esther.h"

namespace es {

LoopExpression::LoopExpression(Expression *condition, Expression *body)
    : condition(condition)
    , body(body) {
}

LoopExpression::~LoopExpression() {
    delete condition;
    delete body;
}

Object *LoopExpression::exec(Esther *esther) {
    Object *volatile value = esther->getNull();

    while (condition->eval(esther)->isTrue())
        value = body->eval(esther);

    return value;
}
}

#include "loopexpression.h"

#include "context.h"
#include "esther.h"

LoopExpression::LoopExpression(Expression *condition, Expression *body)
    : condition(condition)
    , body(body) {
}

LoopExpression::~LoopExpression() {
    delete condition;
    delete body;
}

Pointer<Object> LoopExpression::exec(Esther *esther) {
    Pointer<Object> value = esther->getNull();

    while (condition->eval(esther)->isTrue())
        value = body->eval(esther);

    return value;
}

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

Ptr<Object> LoopExpression::exec(Esther *esther) {
    Ptr<Object> value = esther->getNull();

    while (condition->eval(esther)->isTrue())
        value = body->eval(esther);

    return value;
}

#include "loopexpression.h"

#include "context.h"
#include "runtime.h"

LoopExpression::LoopExpression(Expression *condition, Expression *body)
    : condition(condition), body(body) {
}

LoopExpression::~LoopExpression() {
    delete condition;
    delete body;
}

Object *LoopExpression::exec(Context *context) {
    Object *value = context->getRuntime()->getNull();

    while (condition->eval(context)->isTrue())
        value = body->eval(context);

    return value;
}

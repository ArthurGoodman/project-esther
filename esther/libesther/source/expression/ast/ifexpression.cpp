#include "ifexpression.h"

#include "context.h"
#include "runtime.h"

IfExpression::IfExpression(Expression *condition, Expression *body, Expression *elseBody)
    : condition(condition)
    , body(body)
    , elseBody(elseBody) {
}

IfExpression::~IfExpression() {
    delete condition;
    delete body;
    delete elseBody;
}

Object *IfExpression::exec(Context *context) {
    Object *value = context->getRuntime()->getNull();

    if (condition->eval(context)->isTrue())
        value = body->eval(context);
    else if (elseBody)
        value = elseBody->eval(context);

    return value;
}

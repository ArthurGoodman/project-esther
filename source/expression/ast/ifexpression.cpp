#include "ifexpression.h"

#include "runtime.h"
#include "context.h"

IfExpression::IfExpression(Expression *condition, Expression *body, Expression *elseBody)
    : condition(condition), body(body), elseBody(elseBody) {
}

IObject *IfExpression::exec(Context *context) {
    IObject *value = Runtime::getNull();

    context = context->childContext();

    if (condition->eval(context)->isTrue())
        value = body->eval(context);
    else if (elseBody)
        value = elseBody->eval(context);

    return value;
}

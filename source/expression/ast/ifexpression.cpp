#include "ifexpression.h"

#include "runtime.h"

IfExpression::IfExpression(Expression *condition, Expression *body, Expression *elseBody)
    : condition(condition), body(body), elseBody(elseBody) {
}

IfExpression::~IfExpression() {
    delete condition;
    delete body;
    delete elseBody;
}

Object *IfExpression::eval(Context *context) {
    Object *value = Runtime::getNull();

    if (condition->eval(context)->isTrue())
        value = body->eval(context);
    else if (elseBody)
        value = elseBody->eval(context);

    return value;
}

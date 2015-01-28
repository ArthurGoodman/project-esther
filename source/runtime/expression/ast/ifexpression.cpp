#include "ifexpression.h"

#include "esther.h"

namespace esther {

IfExpression::IfExpression(Expression *condition, Expression *body, Expression *elseBody)
    : condition(condition), body(body), elseBody(elseBody) {
}

IfExpression::~IfExpression() {
    delete condition;
    delete body;
    delete elseBody;
}

Object *IfExpression::eval(Context *context) {
    Object *value = Esther::getNull();

    if (condition->eval(context)->isTrue())
        value = body->eval(context);
    else if (elseBody)
        value = elseBody->eval(context);

    return value;
}
}

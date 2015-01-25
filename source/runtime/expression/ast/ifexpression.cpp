#include "ifexpression.h"

#include "esther.h"

namespace esther {

IfExpression::IfExpression(Expression *condition, Expression *body, Expression *elseBody)
    : condition(condition), body(body), elseBody(elseBody) {
}

Object *IfExpression::eval(Context *context) {
    return Esther::getNull();
}
}

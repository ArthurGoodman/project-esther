#include "ifexpression.h"

#include "context.h"
#include "esther.h"

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

Pointer<Object> IfExpression::exec(Esther *esther) {
    Pointer<Object> value = esther->getNull();

    if (condition->eval(esther)->isTrue())
        value = body->eval(esther);
    else if (elseBody)
        value = elseBody->eval(esther);

    return value;
}

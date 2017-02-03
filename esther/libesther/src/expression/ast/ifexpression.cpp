#include "ifexpression.h"

#include "runtime/object.h"
#include "runtime/context.h"
#include "runtime/esther.h"

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

Ptr<Object> IfExpression::exec(Esther *esther) {
    Ptr<Object> value = esther->getNull();

    if (condition->eval(esther)->isTrue())
        value = body->eval(esther);
    else if (elseBody)
        value = elseBody->eval(esther);

    return value;
}

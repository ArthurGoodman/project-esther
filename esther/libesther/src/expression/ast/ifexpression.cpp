#include "expression/ast/ifexpression.h"

#include "runtime/object.h"
#include "runtime/context.h"
#include "esther.h"

namespace es {

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

Object *IfExpression::exec(Esther *esther) {
    Object *volatile value = esther->getNull();

    if (condition->eval(esther)->isTrue())
        value = body->eval(esther);
    else if (elseBody)
        value = elseBody->eval(esther);

    return value;
}
}

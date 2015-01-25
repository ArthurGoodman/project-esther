#include "whileexpression.h"

#include "esther.h"

namespace esther {

WhileExpression::WhileExpression(Expression *condition, Expression *body, Expression *elseBody)
    : condition(condition), body(body), elseBody(elseBody) {
}

Object *WhileExpression::eval(Context *context) {
    return Esther::getNull();
}
}

#include "doexpression.h"

#include "esther.h"

namespace esther {

DoExpression::DoExpression(Expression *body, Expression *condition)
    : body(body), condition(condition) {
}

Object *DoExpression::eval(Context *context) {
    return Esther::getNull();
}
}

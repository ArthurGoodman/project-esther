#include "forexpression.h"

#include "esther.h"

namespace esther {

ForExpression::ForExpression(Expression *preffix, Expression *condition, Expression *suffix, Expression *body)
    : preffix(preffix), condition(condition), suffix(suffix), body(body) {
}

Object *ForExpression::eval(Context *context) {
    return Esther::getNull();
}
}

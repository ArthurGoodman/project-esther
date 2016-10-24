#include "callexpression.h"

CallExpression::CallExpression(Expression *self, Expression *body, const std::list<Expression *> &args)
    : self(self), body(body), args(args) {
}

Object *CallExpression::exec(Context *) {
    return 0;
}

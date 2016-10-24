#include "callexpression.h"

#include "common.h"

CallExpression::CallExpression(Expression *body, const std::list<Expression *> &args)
    : body(body), args(args) {
}

CallExpression::~CallExpression() {
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *CallExpression::exec(Context *context) {
    return 0;
}

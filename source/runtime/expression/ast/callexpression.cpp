#include "callexpression.h"

#include "esther.h"

namespace esther {

CallExpression::CallExpression(Expression *self, string name, list<Expression *> args)
    : self(self), name(name), args(args) {
}

Object *CallExpression::eval(Context *context) {
    return Esther::getNull();
}
}

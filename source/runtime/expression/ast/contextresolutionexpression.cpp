#include "contextresolutionexpression.h"

#include "esther.h"

namespace esther {

ContextResolutionExpression::ContextResolutionExpression(Expression *self, Expression *body)
    : self(self), body(body) {
}

Object *ContextResolutionExpression::eval(Context *context) {
    return Esther::getNull();
}
}

#include "contextresolutionexpression.h"

#include "context.h"
#include "function.h"

ContextResolutionExpression::ContextResolutionExpression(Expression *self, Expression *body)
    : self(self), body(body) {
}

Object *ContextResolutionExpression::eval(Context *context) {
    Object *self = this->self->eval(context);
    return body->eval(context->objectChildContext(self));
}

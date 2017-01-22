#include "contextresolutionexpression.h"

#include "context.h"
#include "runtime.h"

ContextResolutionExpression::ContextResolutionExpression(Expression *self, Expression *body)
    : self(self)
    , body(body) {
}

ContextResolutionExpression::~ContextResolutionExpression() {
    delete self;
    delete body;
}

Object *ContextResolutionExpression::exec(Context *context) {
    return body->eval(context->childContext(self->eval(context), context->getRuntime()->createObject()));
}

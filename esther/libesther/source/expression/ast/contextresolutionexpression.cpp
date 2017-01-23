#include "contextresolutionexpression.h"

#include "context.h"
#include "runtime.h"

ContextResolutionExpression::ContextResolutionExpression(Expression *self, Expression *body, bool object)
    : self(self)
    , body(body)
    , object(object) {
}

ContextResolutionExpression::~ContextResolutionExpression() {
    delete self;
    delete body;
}

Object *ContextResolutionExpression::exec(Context *context) {
    Object *evaledSelf = self->eval(context);
    Object *evaledHere = object ? evaledSelf : context->getRuntime()->createObject();
    return body->eval(context->childContext(evaledSelf, evaledHere));
}

#include "contextresolutionexpression.h"

#include "context.h"
#include "runtime.h"

ContextResolutionExpression::ContextResolutionExpression(Expression *self, Expression *body, Context *context)
    : self(self), body(body), context(context) {
}

ContextResolutionExpression::~ContextResolutionExpression() {
    delete self;
    delete body;
}

Object *ContextResolutionExpression::exec(Context *context) {
    this->context->pushSelf(self->eval(context));
    this->context->pushHere(context->getRuntime()->createObject());

    Object *value = body->eval(this->context);

    this->context->popSelf();
    this->context->popHere();

    return value;
}

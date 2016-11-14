#include "contextresolutionexpression.h"

#include "context.h"

ContextResolutionExpression::ContextResolutionExpression(Expression *self, Expression *body, Context *context)
    : self(self), body(body), context(context) {
}

ContextResolutionExpression::~ContextResolutionExpression() {
    delete self;
    delete body;
}

Object *ContextResolutionExpression::exec(Context *context) {
    this->context->pushSelf(self->eval(context));
    //this->context->clear();

    Object *value = body->eval(this->context);

    this->context->popSelf();

    return value;
}

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
    this->context->setSelf(self->eval(context));
    this->context->clear();

    return body->eval(this->context);
}

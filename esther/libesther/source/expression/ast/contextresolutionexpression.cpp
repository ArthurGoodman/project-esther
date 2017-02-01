#include "contextresolutionexpression.h"

#include "context.h"
#include "esther.h"

ContextResolutionExpression::ContextResolutionExpression(Expression *self, Expression *body, Expression *here)
    : self(self)
    , body(body)
    , here(here) {
}

ContextResolutionExpression::~ContextResolutionExpression() {
    delete self;
    delete body;
    delete here;
}

Pointer<Object> ContextResolutionExpression::exec(Esther *esther) {
    Pointer<Object> evaledSelf = self->eval(esther);
    Pointer<Object> evaledHere = here ? here->eval(esther) : evaledSelf;

    esther->pushContext(esther->context()->childContext(evaledSelf, evaledHere));
    Pointer<Object> value = body->eval(esther);
    esther->popContext();

    return value;
}

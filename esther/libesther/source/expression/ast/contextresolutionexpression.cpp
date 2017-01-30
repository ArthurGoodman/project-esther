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

Object *ContextResolutionExpression::exec(Esther *esther) {
    Object *evaledSelf = self->eval(esther);
    Object *evaledHere = here ? here->eval(esther) : evaledSelf;

    esther->pushContext(evaledSelf, evaledHere);
    Object *value = body->eval(esther);
    esther->popContext();

    return value;
}

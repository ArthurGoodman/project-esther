#include "contextresolutionexpression.h"

#include "context.h"
#include "esther.h"

ContextResolutionExpression::ContextResolutionExpression(Expression *self, Expression *here, Expression *body)
    : self(self)
    , here(here)
    , body(body) {
}

ContextResolutionExpression::~ContextResolutionExpression() {
    delete self;
    delete here;
    delete body;
}

Object *ContextResolutionExpression::exec(Esther *esther) {
    Object *evaledSelf = self->eval(esther);
    Object *evaledHere = here ? here->eval(esther) : evaledSelf;

    esther->pushChildContext(evaledSelf, evaledHere);
    Object *value = body->eval(esther);
    esther->popContext();

    return value;
}

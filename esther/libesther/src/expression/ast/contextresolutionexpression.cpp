#include "expression/ast/contextresolutionexpression.h"

#include "runtime/context.h"
#include "esther.h"

namespace es {

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

    esther->pushContext(esther->context()->childContext(evaledSelf, evaledHere));
    Object *value = body->eval(esther);
    esther->popContext();

    return value;
}
}

#include "contextcallepression.h"

#include "common.h"
#include "context.h"

ContextCallEpression::ContextCallEpression(Expression *self, Expression *body, const std::list<Expression *> &args)
    : self(self), body(body), args(args) {
}

ContextCallEpression::~ContextCallEpression() {
    delete self;
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *ContextCallEpression::exec(Context *context) {
    std::list<Object *> evaledArgs;

    evaledArgs << (self == 0 ? context->getSelf() : self->eval(context));

    Object *evaledBody = body->eval(context);

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    return evaledBody->call("()", evaledArgs);
}

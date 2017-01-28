#include "Contextcallexpression.h"

#include "common.h"
#include "context.h"
#include "esther.h"
#include "function.h"

ContextCallExpression::ContextCallExpression(Expression *self, Expression *body, const std::list<Expression *> &args)
    : self(self)
    , body(body)
    , args(args) {
}

ContextCallExpression::~ContextCallExpression() {
    delete self;
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *ContextCallExpression::exec(Esther *esther) {
    Object *evaledSelf = self->eval(esther);

    esther->pushChildContext(evaledSelf, esther->createObject());
    Object *f = body->eval(esther);
    esther->popContext();

    if (dynamic_cast<Function *>(f)) {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size());

        for (Expression *e : args)
            evaledArgs << e->eval(esther);

        return ((Function *)f)->invoke(esther, evaledSelf, evaledArgs);
    } else {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size() + 1);

        evaledArgs << evaledSelf;

        for (Expression *e : args)
            evaledArgs << e->eval(esther);

        return f->call(esther, "()", evaledArgs);
    }
}

#include "Contextcallexpression.h"

#include "common.h"
#include "context.h"
#include "runtime.h"
#include "function.h"

ContextCallExpression::ContextCallExpression(Expression *self, Expression *body, const std::list<Expression *> &args, Context *context)
    : self(self), body(body), args(args), context(context) {
}

ContextCallExpression::~ContextCallExpression() {
    delete self;
    delete body;

    for (Expression *e : args)
        delete e;
}

Object *ContextCallExpression::exec(Context *context) {
    Object *evaledSelf = self->eval(context);

    this->context->pushSelf(evaledSelf);
    this->context->pushHere(context->getRuntime()->createObject());

    Object *f = body->eval(this->context);

    this->context->popSelf();
    this->context->popHere();

    if (dynamic_cast<Function *>(f)) {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size());

        for (Expression *e : args)
            evaledArgs << e->eval(context);

        return ((Function *)f)->invoke(evaledSelf, evaledArgs);
    } else {
        std::vector<Object *> evaledArgs;
        evaledArgs.reserve(args.size() + 1);

        evaledArgs << evaledSelf;

        for (Expression *e : args)
            evaledArgs << e->eval(context);

        return f->call("()", evaledArgs);
    }
}
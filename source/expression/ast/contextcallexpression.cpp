#include "contextcallexpression.h"

#include "common.h"
#include "context.h"
#include "function.h"
#include "method.h"
#include "tuple.h"

ContextCallExpression::ContextCallExpression(Expression *self, Expression *body, std::list<Expression *> args)
    : self(self), body(body), args(args) {
}

IObject *ContextCallExpression::exec(Context *context) {
    IObject *self = this->self->eval(context);

    Context *selfContext = context->objectChildContext(self);

    IObject *body = this->body->eval(selfContext);

    std::list<IObject *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    Tuple *actualArgs;

    if (dynamic_cast<Method *>(body))
        actualArgs = new Tuple({selfContext->getSelfForMethod((Method *)body), new Tuple(evaledArgs)});
    else if (dynamic_cast<Function *>(body))
        actualArgs = new Tuple({self, new Tuple(evaledArgs)});
    else
        actualArgs = new Tuple(evaledArgs);

    IObject *value = body->call("()", actualArgs);

    return value;
}

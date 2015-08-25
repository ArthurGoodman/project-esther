#include "contextcallexpression.h"

#include "context.h"
#include "function.h"
#include "tuple.h"

ContextCallExpression::ContextCallExpression(Expression *self, Expression *body, list<Expression *> args)
    : self(self), body(body), args(args) {
}

Object *ContextCallExpression::eval(Context *context) {
    Object *self = this->self->eval(context);
    Object *body = this->body->eval(context->objectChildContext(self));

    list<Object *> evaledArgs;

    foreach (i, args)
        evaledArgs << (*i)->eval(context);

    Tuple *actualArgs;

    if (dynamic_cast<Function *>(body))
        actualArgs = new Tuple({self, new Tuple(evaledArgs)});
    else
        actualArgs = new Tuple(evaledArgs);

    Object *value = body->call("()", actualArgs);

    return value;
}

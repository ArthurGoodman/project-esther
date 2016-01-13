#include "callexpression.h"

#include "runtime.h"
#include "tuple.h"
#include "function.h"
#include "context.h"
#include "method.h"

CallExpression::CallExpression(Expression *self, string name, list<Expression *> args)
    : self(self), name(name), args(args) {
}

Object *CallExpression::exec(Context *context) {
    Object *self = this->self->eval(context);

    list<Object *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    Tuple *actualArgs;

    if (dynamic_cast<Method *>(self) && name == "()")
        actualArgs = new Tuple({context->getSelfForMethod((Method *)self), new Tuple(evaledArgs)});
    else if (/*dynamic_cast<Function *>(self) && */name == "()")
        actualArgs = new Tuple({context->getCurrentSelf(), new Tuple(evaledArgs)});
    else
        actualArgs = new Tuple(evaledArgs);

    Object *value = self->call(name, actualArgs);

    return value;
}

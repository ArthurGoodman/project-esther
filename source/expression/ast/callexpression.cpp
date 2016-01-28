#include "callexpression.h"

#include "iobject.h"
#include "runtime.h"
#include "tuple.h"
#include "function.h"
#include "context.h"
#include "method.h"

CallExpression::CallExpression(Expression *self, string name, list<Expression *> args)
    : self(self), name(name), args(args) {
}

IObject *CallExpression::exec(Context *context) {
    IObject *self = this->self->eval(context);

    list<IObject *> evaledArgs;

    for (Expression *e : args)
        evaledArgs << e->eval(context);

    Tuple *actualArgs;

    if (dynamic_cast<Method *>(self) && name == "()")
        actualArgs = new Tuple({context->getSelfForMethod((Method *)self), new Tuple(evaledArgs)});
    else if (dynamic_cast<Function *>(self) && name == "()")
        actualArgs = new Tuple({context->getCurrentSelf(), new Tuple(evaledArgs)});
    else
        actualArgs = new Tuple(evaledArgs);

    IObject *value = self->call(name, actualArgs);

    return value;
}

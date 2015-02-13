#include "callexpression.h"

#include "runtime.h"
#include "tuple.h"
#include "function.h"
#include "context.h"

namespace esther {

CallExpression::CallExpression(Expression *self, string name, list<Expression *> args)
    : self(self), name(name), args(args) {
}

Object *CallExpression::eval(Context *context) {
    Object *self = this->self->eval(context);

    list<Object *> evaledArgsList;

    foreach (i, args)
        evaledArgsList << (*i)->eval(context);

    if (dynamic_cast<Function *>(self))
        evaledArgsList.push_front(context->getCurrentSelf());

    Tuple *evaledArgs = new Tuple(evaledArgsList);

    Object *value = self->call(name, evaledArgs);

    return value;
}
}

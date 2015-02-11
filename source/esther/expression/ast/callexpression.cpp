#include "callexpression.h"

#include "runtime.h"
#include "tuple.h"
#include "callstack.h"
#include "call.h"

namespace esther {

CallExpression::CallExpression(Expression *self, string name, list<Expression *> args)
    : self(self), name(name), args(args) {
}

Object *CallExpression::eval(Context *context) {
    Object *self = this->self->eval(context);

    list<Object *> evaledArgsList;

    foreach (i, args)
        evaledArgsList << (*i)->eval(context);

    Tuple *evaledArgs = new Tuple(evaledArgsList);

    Runtime::getCallStack()->beginCall(new esther::Call(context, evaledArgs));
    Object *value = self->call(name, evaledArgs);
    Runtime::getCallStack()->endCall();

    return value;
}
}

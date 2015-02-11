#include "function.h"

#include "context.h"
#include "functionbody.h"
#include "tuple.h"

namespace esther {

Function::Function(string className, string name, Context *context, list<string> params, FunctionBody *body)
    : Object(className), name(name), context(context), params(params), body(body) {
}

Function::Function(string name, Context *context, list<string> params, FunctionBody *body)
    : Object("Function"), name(name), context(context), params(params), body(body) {
}

Object *Function::invoke(Object *self, Tuple *args) {
    context = context->childContext(self);

    int c = 0;
    foreach (i, params)
        context->setLocal(*i, args->at(c));

    return body->eval(context);
}

//string Function::toString() {
//    return name.empty() ? "<Anonymous Function>" : name;
//}
}

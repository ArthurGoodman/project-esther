#include "function.h"

#include "context.h"
#include "block.h"
#include "tuple.h"
#include "logger.h"

namespace esther {

Function::Function(string className, string name, Context *context, list<string> params, Block *body)
    : Object(className), name(name), context(context), params(params), body(body) {
}

Function::Function(string name, Context *context, list<string> params, Block *body)
    : Object("Function"), name(name), context(context), params(params), body(body) {
}

string Function::getName() {
    return name;
}

Object *Function::invoke(Object *self, Tuple *args) {
    context = context->childContext(self);

    foreach (i, params)
        context->setLocal(*i, args->at(distance(params.begin(), i)));

    return body->eval(context);
}

string Function::toString() {
    return name.empty() ? "<anonymous function>" : "<function " + name + ">";
}
}

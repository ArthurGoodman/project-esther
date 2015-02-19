#include "function.h"

#include "runtime.h"
#include "context.h"
#include "block.h"
#include "tuple.h"
#include "logger.h"
#include "signature.h"

Function::Function(string className, string name, Context *context, Signature *signature, list<string> params, Block *body)
    : Object(className), name(name), context(context), signature(signature), params(params), body(body) {
}

Function::Function(string name, Context *context, Signature *signature, list<string> params, Block *body)
    : Object("Function"), name(name), context(context), signature(signature), params(params), body(body) {
}

string Function::getName() {
    return name;
}

Signature *Function::getSignature() {
    return signature;
}

Object *Function::invoke(Object *self, Tuple *args) {
    check(self, args);

    context = context->childContext(self);

    foreach (i, params)
        context->setLocal(*i, args->at(distance(params.begin(), i)));

    return body->eval(context);
}

string Function::toString() {
    return name.empty() ? "<anonymous function>" : "<function " + name + ">";
}

void Function::check(Object *self, Tuple *args) {
    if (!signature->accepts(args))
        Runtime::runtimeError("invalid arguments");

    args = signature->convert(args);
}

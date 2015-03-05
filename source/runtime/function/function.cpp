#include "function.h"

#include "runtime.h"
#include "context.h"
#include "block.h"
#include "tuple.h"
#include "logger.h"
#include "signature.h"
#include "returnexception.h"
#include "functionfeature.h"
#include "argumentscheckerfeature.h"

Function::Function(string className, string name, Context *context, Signature *signature, Block *body)
    : Object(className), name(name), context(context), signature(signature), body(body) {
    addFeature(new ArgumentsCheckerFeature(signature));
}

Function::Function(string name, Context *context, Signature *signature, Block *body)
    : Object("Function"), name(name), context(context), signature(signature), body(body) {
    addFeature(new ArgumentsCheckerFeature(signature));
}

string Function::getName() {
    return name;
}

Signature *Function::getSignature() {
    return signature;
}

Block *Function::getBody() {
    return body;
}

Object *Function::invoke(Object *self, Tuple *args) {
    foreach (i, features)
        (*i)->check(self, args);

    return execute(self, args);
}

Object *Function::execute(Object *self, Tuple *args) {
    args = signature->convert(args);

    context = context->childContext(self);

    list<string> params = signature->paramsNames();

    context->setLocal("arguments" ,args);

    foreach (i, params)
        context->setLocal(*i, args->at(distance(params.begin(), i)));

    try {
        return body->eval(context);
    } catch (ReturnException *e) {
        Object *value = e->value();
        delete e;
        return value;
    } catch (Exception *e) {
        e->raise();
        return 0;
    }
}

string Function::toString() {
    return name.empty() ? "<anonymous function>" : "<function " + name + ">";
}

void Function::addFeature(FunctionFeature *feature) {
    features << feature;
}

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
    for (FunctionFeature *f : features)
        f->check(self, args);

    return execute(self, args);
}

Object *Function::execute(Object *self, Tuple *args) {
    args = signature->convert(args);

    context = context->objectChildContext(self)->childContext();

    list<string> params = signature->paramsNames();

    context->setLocal("arguments", args);

    int i = 0;
    for (string s : params)
        context->setLocal(s, args->at(i++));

    Object *returnValue = 0;

    try {
        returnValue = body->eval(context);
    } catch (ReturnException *e) {
        returnValue = e->value();
        delete e;
    } catch (Exception *e) {
        e->raise();
        return 0;
    }

    return signature->convertReturnValue(returnValue);
}

string Function::toString() {
    return name.empty() ? "<anonymous function>" : "<function " + name + ">";
}

Object *Function::clone() {
    Function *clone = new Function(name, context, signature, body);
    clone->features = features;
    return clone;
}

void Function::addFeature(FunctionFeature *feature) {
    features << feature;
}

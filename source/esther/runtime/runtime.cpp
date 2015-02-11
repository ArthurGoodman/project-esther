#include "runtime.h"

#include "class.h"
#include "context.h"
#include "lexer.h"
#include "parser.h"
#include "expression.h"
#include "true.h"
#include "false.h"
#include "null.h"
#include "runtimeerror.h"

#include "method.h"
#include "nativefunctionbody.h"
#include "io.h"
#include "tuple.h"
#include "callstack.h"
#include "valueobject.h"

namespace esther {

Context *Runtime::root;

Object *Runtime::mainObject;
Class *Runtime::objectClass;

Object *Runtime::trueObject;
Object *Runtime::falseObject;
Object *Runtime::nullObject;

map<string, Class *> Runtime::rootClasses;

CallStack *Runtime::callStack;

void Runtime::initialize() {
    objectClass = new Class("Object", 0);
    setRootClass(objectClass);

    mainObject = new Object;

    Class *classClass = new Class("Class");
    setRootClass(classClass);

    objectClass->setClass(classClass);
    classClass->setClass(classClass);

    setRootClass("Function");
    setRootClass("Method", "Function");

    setRootClass("TrueClass");
    trueObject = new True;

    setRootClass("FalseClass");
    falseObject = new False;

    setRootClass("NullClass");
    nullObject = new Null;

    //setRootClass("MethodList", "Method");
    //setRootClass("Function", "Callable");
    //setRootClass("Lambda", "Callable");

    setRootClass("Integer");
    setRootClass("Float");
    setRootClass("Char");
    setRootClass("String");

    setRootClass("Context");

    root = new Context;

    objectClass->setMethod("print",
                           new Method("print", root, list<string>(1, "arg"),
                                      new NativeFunctionBody([](Object *, Tuple * args) -> Object * {
                                                   IO::print(args->at(0)->toString());
                                                   return Runtime::getNull();
                                      })));

    getRootClass("Integer")->setMethod("+",
                                       new Method("+", root, list<string>(1, "arg"),
                                                  new NativeFunctionBody([](Object * self, Tuple * args) -> Object * {
                                                               return new ValueObject(((ValueObject *)self)->getVariant().toInteger() + ((ValueObject *)args->at(0))->getVariant().toInteger());
                                                  })));

    callStack = new CallStack;
}

void Runtime::release() {
    delete root;

    delete mainObject;

    delete trueObject;
    delete falseObject;
    delete nullObject;

    foreach (i, rootClasses)
        delete i->second;

    delete callStack;
}

Context *Runtime::getRoot() {
    return root;
}

Object *Runtime::getMainObject() {
    return mainObject;
}

Class *Runtime::getObjectClass() {
    return objectClass;
}

Object *Runtime::getTrue() {
    return trueObject;
}

Object *Runtime::getFalse() {
    return falseObject;
}

Object *Runtime::getNull() {
    return nullObject;
}

CallStack *Runtime::getCallStack() {
    return callStack;
}

bool Runtime::hasRootClass(string name) {
    return rootClasses.find(name) != rootClasses.end();
}

Class *Runtime::getRootClass(string name) {
    return rootClasses.find(name) != rootClasses.end() ? rootClasses[name] : 0;
}

void Runtime::setRootClass(Class *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

void Runtime::setRootClass(string name) {
    rootClasses[name] = new Class(name);
}

void Runtime::setRootClass(string name, string superName) {
    rootClasses[name] = new Class(name, superName);
}

Object *Runtime::toBoolean(bool value) {
    return value ? trueObject : falseObject;
}

void Runtime::runtimeError(string message) {
    throw new RuntimeError(message);
}
}

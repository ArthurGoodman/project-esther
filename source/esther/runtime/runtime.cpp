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

namespace esther {

Context *Runtime::root;

Object *Runtime::mainObject;
Class *Runtime::objectClass;

Object *Runtime::trueObject;
Object *Runtime::falseObject;
Object *Runtime::nullObject;

map<string, Class *> Runtime::rootClasses;

void Runtime::initialize() {
    objectClass = new Class("Object", 0);
    setRootClass(objectClass);

    mainObject = new Object;

    Class *classClass = new Class("Class");
    setRootClass(classClass);

    objectClass->setClass(classClass);
    classClass->setClass(classClass);

    //Class *methodClass = new Class("Method", 0, 0); setRootClass(methodClass);
    //Class *callableClass = new Class("Callable"); setRootClass(callableClass);
    //methodClass->setSuperclass(callableClass);

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
}

void Runtime::release() {
    delete root;

    delete mainObject;

    delete trueObject;
    delete falseObject;
    delete nullObject;

    foreach (i, rootClasses)
        delete i->second;
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

#include "esther.h"

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

Context *Esther::root;
Object *Esther::mainObject;
Class *Esther::objectClass;
Object *Esther::trueObject;
Object *Esther::falseObject;
Object *Esther::nullObject;

map<string, Class *> Esther::rootClasses;

Lexer *Esther::lexer;
Parser *Esther::parser;
stack<string> Esther::sources;

void Esther::initialize() {
    lexer = Lexer::create();
    parser = Parser::create();

    Expression::initialize();

    initializeRuntime();
}

void Esther::release() {
    delete lexer;
    delete parser;

    Expression::release();

    releaseRuntime();
}

void Esther::initializeRuntime() {
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

void Esther::releaseRuntime() {
    delete root;

    delete mainObject;

    delete trueObject;
    delete falseObject;
    delete nullObject;

    foreach (i, rootClasses)
        delete i->second;
}

Context *Esther::getRoot() {
    return root;
}

Object *Esther::getMainObject() {
    return mainObject;
}

Class *Esther::getObjectClass() {
    return objectClass;
}

Object *Esther::getTrue() {
    return trueObject;
}

Object *Esther::getFalse() {
    return falseObject;
}

Object *Esther::getNull() {
    return nullObject;
}

bool Esther::hasRootClass(string name) {
    return rootClasses.find(name) != rootClasses.end();
}

Class *Esther::getRootClass(string name) {
    return rootClasses.find(name) != rootClasses.end() ? rootClasses[name] : 0;
}

void Esther::setRootClass(Class *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

void Esther::setRootClass(string name) {
    rootClasses[name] = new Class(name);
}

void Esther::setRootClass(string name, string superName) {
    rootClasses[name] = new Class(name, superName);
}

Object *Esther::toBoolean(bool value) {
    return value ? trueObject : falseObject;
}

void Esther::runtimeError(string message) {
    throw new RuntimeError(message);
}

void Esther::pushSource(const string &source) {
    sources.push(source);
}

void Esther::popSource() {
    if (!sources.empty())
        sources.pop();
}

const string &Esther::source() {
    return sources.top();
}
}

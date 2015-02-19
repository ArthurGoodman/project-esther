#include "runtime.h"

#include "rootclass.h"
#include "context.h"
#include "lexer.h"
#include "parser.h"
#include "expression.h"
#include "true.h"
#include "false.h"
#include "null.h"
#include "runtimeerror.h"
//#include "callstack.h"
#include "objectclass.h"
#include "classclass.h"
#include "functionclass.h"
#include "methodclass.h"
#include "booleanclass.h"
#include "nullclass.h"
#include "integerclass.h"
#include "floatclass.h"
#include "characterclass.h"
#include "stringclass.h"
#include "tupleclass.h"
#include "contextclass.h"
#include "interfaceclass.h"

Context *Runtime::root;

Object *Runtime::mainObject;
Class *Runtime::objectClass;

Object *Runtime::trueObject;
Object *Runtime::falseObject;
Object *Runtime::nullObject;

map<string, RootClass *> Runtime::rootClasses;

//CallStack *Runtime::callStack;

void Runtime::initialize() {
    objectClass = new ObjectClass;

    new ClassClass;

    new FunctionClass;
    new MethodClass;

    new BooleanClass;
    new NullClass;

    new IntegerClass;
    new FloatClass;
    new CharacterClass;
    new StringClass;

    new TupleClass;

    new ContextClass;

    mainObject = new Object;

    trueObject = new True;
    falseObject = new False;
    nullObject = new Null;

    root = new Context;

    //callStack = new CallStack;

    new InterfaceClass;

    foreach (i, rootClasses)
        i->second->setupMethods();
}

void Runtime::release() {
    delete root;

    delete mainObject;

    delete trueObject;
    delete falseObject;
    delete nullObject;

    foreach (i, rootClasses)
        delete i->second;

    //delete callStack;
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

//CallStack *Runtime::getCallStack() {
//    return callStack;
//}

//void Runtime::beginCall(Call *call) {
//    callStack->beginCall(call);
//}

//void Runtime::endCall() {
//    callStack->endCall();
//}

bool Runtime::hasRootClass(string name) {
    return rootClasses.find(name) != rootClasses.end();
}

Class *Runtime::getRootClass(string name) {
    return rootClasses.find(name) != rootClasses.end() ? rootClasses[name] : 0;
}

void Runtime::setRootClass(RootClass *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

Object *Runtime::toBoolean(bool value) {
    return value ? trueObject : falseObject;
}

void Runtime::runtimeError(string message) {
    throw new RuntimeError(message);
}

#include "runtime.h"

#include "rootclass.h"
#include "objectcontext.h"
#include "ilexer.h"
#include "iparser.h"
#include "expression.h"
#include "true.h"
#include "false.h"
#include "null.h"
#include "runtimeerror.h"
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
#include "blockclass.h"
#include "rangeclass.h"
#include "overloadedmethodclass.h"
#include "mathlib.h"

Context *Runtime::root;

IObject *Runtime::mainObject;
Class *Runtime::objectClass;

IObject *Runtime::trueObject;
IObject *Runtime::falseObject;
IObject *Runtime::nullObject;

std::map<std::string, RootClass *> Runtime::rootClasses;

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

    new BlockClass;

    new RangeClass;

    new OverloadedMethodClass;

    mainObject = new Object;

    trueObject = new True;
    falseObject = new False;
    nullObject = new Null;

    root = new ObjectContext;

    for (auto c : rootClasses)
        c.second->setupMethods();

    Math::initialize();
}

void Runtime::release() {
    delete root;

    delete mainObject;

    delete trueObject;
    delete falseObject;
    delete nullObject;

    for (auto c : rootClasses)
        delete c.second;
}

Context *Runtime::getRoot() {
    return root;
}

IObject *Runtime::getMainObject() {
    return mainObject;
}

Class *Runtime::getObjectClass() {
    return objectClass;
}

IObject *Runtime::getTrue() {
    return trueObject;
}

IObject *Runtime::getFalse() {
    return falseObject;
}

IObject *Runtime::getNull() {
    return nullObject;
}

bool Runtime::hasRootClass(const std::string &name) {
    return rootClasses.find(name) != rootClasses.end();
}

Class *Runtime::getRootClass(const std::string &name) {
    return rootClasses.find(name) != rootClasses.end() ? rootClasses[name] : 0;
}

void Runtime::setRootClass(RootClass *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

IObject *Runtime::toBoolean(bool value) {
    return value ? trueObject : falseObject;
}

void Runtime::runtimeError(const std::string &message) {
    throw new RuntimeError(message);
}

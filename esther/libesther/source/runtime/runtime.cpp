#include "runtime.h"

#include "class.h"
#include "runtimeerror.h"

void Runtime::runtimeError(const std::string &message) {
    throw new RuntimeError(message);
}

Runtime::Runtime() {
    initialize();
}

Runtime::~Runtime() {
    release();
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

bool Runtime::hasRootClass(const std::string &name) {
    return rootClasses.find(name) != rootClasses.end();
}

Class *Runtime::getRootClass(const std::string &name) {
    return rootClasses.find(name) != rootClasses.end() ? rootClasses[name] : 0;
}

void Runtime::setRootClass(Class *rootClass) {
    rootClasses[rootClass->getName()] = rootClass;
}

Object *Runtime::toBoolean(bool value) {
    return value ? trueObject : falseObject;
}

void Runtime::initialize() {
}

void Runtime::release() {
}

#include "runtime.h"

#include "class.h"

Context *Runtime::root;

Object *Runtime::mainObject = 0;
Class *Runtime::objectClass = 0;

Object *Runtime::trueObject = 0;
Object *Runtime::falseObject = 0;
Object *Runtime::nullObject = 0;

std::map<std::string, Class *> Runtime::rootClasses;

void Runtime::initialize() {
}

void Runtime::release() {
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

void Runtime::runtimeError(const std::string &message) {
}

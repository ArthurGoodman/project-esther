#include "object.h"

#include "runtime.h"
#include "class.h"
#include "io.h"
#include "utility.h"
#include "tuple.h"
#include "method.h"

Object::Object()
    : objectClass(Runtime::getObjectClass()) {
}

Object::Object(Class *objectClass)
    : objectClass(objectClass) {
}

Object::Object(string className)
    : objectClass((Class *)Runtime::getRootClass(className)) {
}

Object::~Object() {
}

Class *Object::getClass() {
    return objectClass;
}

void Object::setClass(Class *objectClass) {
    this->objectClass = objectClass;
}

bool Object::hasAttribute(string name) {
    return attributes.find(name) != attributes.end();
}

Object *Object::getAttribute(string name) {
    return hasAttribute(name) ? attributes.at(name) : 0;
}

void Object::setAttribute(string name, Object *value) {
    attributes[name] = value;
}

bool Object::is(Class *_class) {
    return false;
}

bool Object::is(string className) {
    return is((Class *)Runtime::getRootClass(className));
}

bool Object::converts(Class *_class) {
    return false;
}

Object *Object::as(Class *_class) {
    return Runtime::getNull();
}

Object *Object::call(string name, Tuple *args) {
    Method *method = objectClass->lookup(name);

    if (!method)
        Runtime::runtimeError("undefined method '" + name + "'");

    return method->invoke(this, args);
}

Object *Object::call(string name, Object *arg) {
    return call(name, new Tuple(list<Object *>(1, arg)));
}

Object *Object::call(string name) {
    return call(name, new Tuple(list<Object *>()));
}

bool Object::isTrue() {
    return true;
}

bool Object::isFalse() {
    return false;
}

bool Object::isNull() {
    return false;
}

string Object::toString() {
    return "<" + objectClass->toString() + ":" + Utility::toString(this) + ">";
}

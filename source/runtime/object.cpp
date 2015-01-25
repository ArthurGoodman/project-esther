#include "object.h"

#include "esther.h"
#include "class.h"
#include "io.h"

namespace esther {

Object::Object()
    : objectClass(Esther::getObjectClass()) {
}

Object::Object(Class *objectClass)
    : objectClass(objectClass) {
}

Object::Object(string className)
    : objectClass(Esther::getRootClass(className)) {
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

bool Object::converts(Class *_class) {
    return false;
}

Object *Object::as(Class *_class) {
    return Esther::getNull();
}

Object *Object::call(string name, list<Object *> args) {
    return Esther::getNull();
}

Object *Object::call(string name, Object *arg) {
    return call(name, list<Object *>(1, arg));
}

Object *Object::call(string name) {
    return call(name, list<Object *>());
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
    return "<" + objectClass->toString() + ":" + ::toString<void *>(this) + ">";
}
}

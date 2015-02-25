#include "object.h"

#include "runtime.h"
#include "class.h"
#include "io.h"
#include "utility.h"
#include "tuple.h"
#include "method.h"
#include "signature.h"

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
    return objectClass->isChild(_class);
}

bool Object::is(string className) {
    return is((Class *)Runtime::getRootClass(className));
}

bool Object::converts(Class *_class) {
    if (is(_class))
        return true;

    if (!_class->hasMethod(_class->getName()))
        return false;

    Method *constructor = _class->getMethod(_class->getName());

    if (!constructor->getSignature()->equals(new Signature(Runtime::getObjectClass(), {objectClass})))
        return false;

    return true;
}

Object *Object::as(Class *_class) {
    if (is(_class))
        return this;

    Method *constructor = _class->getMethod(_class->getName());

    if (!constructor)
        Runtime::runtimeError("can't convert");

    return _class->newInstance(new Tuple({this}));
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

Object *Object::call(string name, Object *arg, string expectedClassName) {
    Object *value = call(name, new Tuple(list<Object *>(1, arg)));

    if(!value->is(Runtime::getRootClass(expectedClassName)))
        Runtime::runtimeError("invalid return class");

    return value;
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

bool Object::equals(Object *other) {
    return call("equals", other, "Boolean")->isTrue();
}

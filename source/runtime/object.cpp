#include "object.h"

#include "runtime.h"
#include "class.h"
#include "io.h"
#include "utility.h"
#include "tuple.h"
#include "method.h"
#include "signature.h"
#include "string.h"
#include "variant.h"

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

    if (!_class->hasMethod("initialize"))
        return false;

    Method *constructor = _class->getMethod("initialize");

    if (!constructor->getSignature()->equals(new Signature(Runtime::getObjectClass(), {objectClass})))
        return false;

    return true;
}

Object *Object::as(Class *_class) {
    if (is(_class))
        return this;

    Method *constructor = _class->getMethod("initialize");

    if (!constructor)
        Runtime::runtimeError("can't convert");

    return _class->newInstance(new Tuple({this}));
}

Object *Object::call(string name, Tuple *args) {
    Object *method = objectClass->lookup(name);

    if (!method) {
        if (hasAttribute(name))
            method = getAttribute(name);
        else
            Runtime::runtimeError("undefined identifier '" + name + "'");
    }

    if(dynamic_cast<Function *>(method))
        return ((Function *)method)->invoke(this, args);
    else
        return method->call("()", new Tuple({this, args}));
}

Object *Object::call(string name, Object *arg) {
    return call(name, new Tuple(list<Object *>(1, arg)));
}

Object *Object::call(string name, Object *arg, string expectedClassName) {
    Object *value = call(name, new Tuple(list<Object *>(1, arg)));

    if (!value->is(Runtime::getRootClass(expectedClassName)))
        Runtime::runtimeError("invalid return class");

    return value;
}

Object *Object::call(string name, string expectedClassName) {
    Object *value = call(name);

    if (!value->is(Runtime::getRootClass(expectedClassName)))
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
    return ((String *)call("toString", "String"))->getVariant().toString();
}

bool Object::equals(Object *other) {
    return call("equals", other, "Boolean")->isTrue();
}

Object *Object::clone() {
    Object *clone = new Object(getClass());
    clone->attributes = attributes;
    return clone;
}

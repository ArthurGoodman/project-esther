#include "dynamicobject.h"

#include "runtime.h"
#include "class.h"
#include "io.h"
#include "utility.h"
#include "tuple.h"
#include "method.h"
#include "signature.h"
#include "string.h"
#include "variant.h"

DynamicObject::DynamicObject()
    : objectClass(Runtime::getObjectClass()) {
}

DynamicObject::DynamicObject(Class *objectClass)
    : objectClass(objectClass) {
}

DynamicObject::DynamicObject(const std::string &className)
    : objectClass((Class *)Runtime::getRootClass(className)) {
}

Class *DynamicObject::getClass() {
    return objectClass;
}

void DynamicObject::setClass(Class *objectClass) {
    this->objectClass = objectClass;
}

bool DynamicObject::hasAttribute(const std::string &name) {
    return attributes.find(name) != attributes.end();
}

IObject *DynamicObject::getAttribute(const std::string &name) {
    return hasAttribute(name) ? attributes.at(name) : 0;
}

void DynamicObject::setAttribute(const std::string &name, IObject *value) {
    attributes[name] = value;
}

bool DynamicObject::is(Class *_class) {
    return objectClass->isChild(_class);
}

bool DynamicObject::is(const std::string &className) {
    return is((Class *)Runtime::getRootClass(className));
}

bool DynamicObject::converts(Class *_class) {
    if (is(_class))
        return true;

    if (!_class->hasMethod("initialize"))
        return false;

    Method *constructor = _class->getMethod("initialize");

    if (!constructor->getSignature()->equals(new Signature(Runtime::getObjectClass(), {objectClass})))
        return false;

    return true;
}

IObject *DynamicObject::as(Class *_class) {
    if (is(_class))
        return this;

    Method *constructor = _class->getMethod("initialize");

    if (!constructor)
        Runtime::runtimeError("can't convert from " + getClass()->callToString() + " to " + _class->callToString());

    return _class->newInstance(new Tuple({this}));
}

IObject *DynamicObject::call(const std::string &name, Tuple *args) {
    IObject *function = hasAttribute(name) ? getAttribute(name) : objectClass->lookup(name);

    if (!function)
        Runtime::runtimeError("undefined identifier '" + name + "'");

    if (dynamic_cast<Function *>(function))
        return ((Function *)function)->invoke(this, args);
    else
        return function->call("()", args);
}

IObject *DynamicObject::call(const std::string &name, IObject *arg, const std::string &expectedClassName) {
    IObject *value = call(name, new Tuple(std::list<IObject *>(1, arg)));

    if (!value->is(Runtime::getRootClass(expectedClassName)))
        Runtime::runtimeError(value->getClass()->callToString() + " is not a valid return type for " + name + " (" + expectedClassName + " expected)");

    return value;
}

IObject *DynamicObject::call(const std::string &name, const std::string &expectedClassName) {
    IObject *value = call(name, new Tuple(std::list<IObject *>()));

    if (!value->is(Runtime::getRootClass(expectedClassName)))
        Runtime::runtimeError(value->getClass()->callToString() + " is not a valid return type for " + name + " (" + expectedClassName + " expected)");

    return value;
}

bool DynamicObject::isTrue() {
    return true;
}

bool DynamicObject::isFalse() {
    return false;
}

bool DynamicObject::callEquals(IObject *other) {
    return call("equals", other, "Boolean")->isTrue();
}

std::string DynamicObject::callToString() {
    return ((String *)call("toString", "String"))->getVariant().toString();
}

bool DynamicObject::equals(IObject *other) {
    return this == other;
}

std::string DynamicObject::toString() {
    return "<" + getClass()->callToString() + ":" + Utility::toString((void *)this) + ">";
}

IObject *DynamicObject::clone() {
    DynamicObject *clone = new DynamicObject(getClass());
    clone->attributes = attributes;
    return clone;
}

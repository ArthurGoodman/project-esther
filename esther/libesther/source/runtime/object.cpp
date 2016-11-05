#include "object.h"

#include "class.h"
#include "runtime.h"
#include "utility.h"
#include "function.h"

Object::Object(Class *objectClass)
    : objectClass(objectClass) {
}

Object::~Object() {
}

Class *Object::getClass() const {
    return objectClass;
}

void Object::setClass(Class *objectClass) {
    this->objectClass = objectClass;
}

bool Object::hasAttribute(const std::string &name) const {
    return attributes.find(name) != attributes.end();
}

Object *Object::getAttribute(const std::string &name) const {
    return attributes.at(name);
}

void Object::setAttribute(const std::string &name, Object *value) {
    attributes[name] = value;
}

Object *Object::get(const std::string &name) const {
    return hasAttribute(name) ? getAttribute(name) : objectClass->lookup(name);
}

void Object::clear() {
    attributes.clear();
}

std::string Object::toString() const {
    return "<" + getClass()->getName() + ":" + Utility::toString((void *)this) + ">";
}

bool Object::isTrue() const {
    return true;
}

Object *Object::call(const std::string &name, const std::vector<Object *> &args) {
    Object *f = get(name);

    if (!f)
        Runtime::runtimeError("undefined field '" + name + "'");

    if (dynamic_cast<Function *>(f))
        return ((Function *)f)->invoke(this, args);

    return f->call("()", args);
}

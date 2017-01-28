#include "object.h"

#include "class.h"
#include "esther.h"
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

bool Object::is(Class *_class) const {
    return objectClass->isChild(_class);
}

std::string Object::toString() const {
    return "<" + getClass()->getName() + ":" + Utility::toString((void *)this) + ">";
}

bool Object::isTrue() const {
    return true;
}

Object *Object::call(Esther *esther, const std::string &name, const std::vector<Object *> &args) {
    Object *f = get(name);

    if (!f)
        Esther::runtimeError("undefined identifier '" + name + "'");

    if (dynamic_cast<Function *>(f))
        return ((Function *)f)->invoke(esther, this, args);

    return f->call(esther, "()", args);
}

Object *Object::callIfFound(Esther *esther, const std::string &name, const std::vector<Object *> &args) {
    Object *f = get(name);

    if (!f)
        return nullptr;

    if (dynamic_cast<Function *>(f))
        return ((Function *)f)->invoke(esther, this, args);

    return f->call(esther, "()", args);
}

Object *Object::call(Esther *esther, const std::string &name, const std::vector<Object *> &args, Class *expectedReturnClass) {
    Object *value = call(esther, name, args);

    if (!value->is(expectedReturnClass))
        Esther::runtimeError(value->getClass()->toString() + " is not a valid return type for " + name + " (" + expectedReturnClass->getName() + " expected)");

    return value;
}

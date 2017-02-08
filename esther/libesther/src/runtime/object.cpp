#include "runtime/object.h"

#include "esther.h"
#include "runtime/class.h"
#include "common/utility.h"
#include "runtime/function.h"

namespace es {

Object::Object(Class *objectClass)
    : objectClass(objectClass)
    , attributes(nullptr) {
}

Object::~Object() {
    delete attributes;
}

Class *Object::getClass() const {
    return objectClass;
}

void Object::setClass(Class *objectClass) {
    this->objectClass = objectClass;
}

bool Object::hasAttribute(const std::string &name) const {
    return attributes && (attributes->find(name) != attributes->end());
}

Object *Object::getAttribute(const std::string &name) const {
    return attributes ? attributes->at(name) : nullptr;
}

void Object::setAttribute(const std::string &name, Object *value) {
    if (!attributes)
        attributes = new std::map<std::string, Object *>;

    (*attributes)[name] = value;
}

Object *Object::get(const std::string &name) const {
    return hasAttribute(name) ? getAttribute(name) : objectClass->lookup(name);
}

bool Object::is(Class *_class) const {
    return objectClass->isChild(_class);
}

std::string Object::toString() const {
    return "<" + getClass()->getName() + ":" + Utility::toString(this) + ">";
}

bool Object::isTrue() const {
    return true;
}

Object *Object::call(Esther *esther, const std::string &name, const std::vector<Object *> &args) {
    Object *f = get(name);

    if (!f)
        Esther::runtimeError("Object::call: undefined identifier '%s'", name.c_str());

    return call(esther, f, args);
}

Object *Object::call(Esther *esther, Object *f, const std::vector<Object *> &args) {
    if (dynamic_cast<Function *>(f))
        return static_cast<Function *>(f)->invoke(esther, this, args);

    std::vector<Object *> actualArgs;
    actualArgs.reserve(args.size() + 1);
    actualArgs << this;
    actualArgs.insert(actualArgs.end(), args.begin(), args.end());

    return f->call(esther, "()", actualArgs);
}

Object *Object::call(Esther *esther, const std::string &name, const std::vector<Object *> &args, Class *expectedReturnClass) {
    Object *value = call(esther, name, args);

    if (!value->is(expectedReturnClass))
        Esther::runtimeError("%s is not a valid return type for %s (%s expected)", value->getClass()->toString().c_str(), name.c_str(), expectedReturnClass->getName().c_str());

    return value;
}

Object *Object::callIfFound(Esther *esther, const std::string &name, const std::vector<Object *> &args) {
    Object *f = get(name);

    if (!f)
        return nullptr;

    return call(esther, f, args);
}
}

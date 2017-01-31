#include "object.h"

#include "class.h"
#include "esther.h"
#include "utility.h"
#include "function.h"

Object::Object(Pointer<Class> objectClass)
    : objectClass(objectClass) {
}

Object::~Object() {
}

Pointer<Class> Object::getClass() const {
    return objectClass;
}

void Object::setClass(Pointer<Class> objectClass) {
    this->objectClass = objectClass;
}

bool Object::hasAttribute(const std::string &name) const {
    return attributes.find(name) != attributes.end();
}

Pointer<Object> Object::getAttribute(const std::string &name) const {
    return attributes.at(name);
}

void Object::setAttribute(const std::string &name, Pointer<Object> value) {
    attributes[name] = value;
}

Pointer<Object> Object::get(const std::string &name) const {
    return hasAttribute(name) ? getAttribute(name) : objectClass->lookup(name);
}

bool Object::is(Pointer<Class> _class) const {
    return objectClass->isChild(_class);
}

std::string Object::toString() const {
    return "<" + getClass()->getName() + ":" + Utility::toString((void *)this) + ">";
}

bool Object::isTrue() const {
    return true;
}

Pointer<Object> Object::call(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args) {
    Pointer<Object> f = get(name);

    if (!f)
        Esther::runtimeError("Object::call: undefined identifier '" + name + "'");

    return call(esther, f, args);
}

Pointer<Object> Object::call(Esther *esther, Pointer<Object> f, const std::vector<Pointer<Object>> &args) {
    if (dynamic_cast<Function *>(*f))
        return ((Function *)*f)->invoke(esther, this, args);

    std::vector<Pointer<Object>> actualArgs;
    actualArgs.reserve(args.size() + 1);
    actualArgs << this;
    actualArgs.insert(actualArgs.end(), args.begin(), args.end());

    return f->call(esther, "()", actualArgs);
}

Pointer<Object> Object::call(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args, Pointer<Class> expectedReturnClass) {
    Pointer<Object> value = call(esther, name, args);

    if (!value->is(expectedReturnClass))
        Esther::runtimeError(value->getClass()->toString() + " is not a valid return type for " + name + " (" + expectedReturnClass->getName() + " expected)");

    return value;
}

Pointer<Object> Object::callIfFound(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args) {
    Pointer<Object> f = get(name);

    if (!f)
        return nullptr;

    return call(esther, f, args);
}

void Object::copy(ManagedObject *dst) {
    new (dst) Object(*this);
}

int Object::getSize() const {
    return sizeof *this;
}

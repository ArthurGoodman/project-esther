#include "object.h"

#include "class.h"
#include "esther.h"
#include "utility.h"
#include "function.h"

Object::Object(Pointer<Class> objectClass)
    : objectClass(objectClass)
    , attributes(nullptr) {
}

Object::~Object() {
    delete attributes;
}

Pointer<Class> Object::getClass() const {
    return objectClass;
}

void Object::setClass(Pointer<Class> objectClass) {
    this->objectClass = objectClass;
}

bool Object::hasAttribute(const std::string &name) const {
    return attributes && (attributes->find(name) != attributes->end());
}

Pointer<Object> Object::getAttribute(const std::string &name) const {
    return attributes ? attributes->at(name) : nullptr;
}

void Object::setAttribute(const std::string &name, Pointer<Object> value) {
    if (!attributes)
        attributes = new std::map<std::string, Pointer<Object>>;

    (*attributes)[name] = value;
}

Pointer<Object> Object::get(const std::string &name) const {
    Pointer<const Object> _this = this;

    return _this->hasAttribute(name) ? _this->getAttribute(name) : _this->objectClass->lookup(name);
}

bool Object::is(Pointer<Class> _class) const {
    Pointer<const Object> _this = this;

    return _this->objectClass->isChild(_class);
}

std::string Object::toString() const {
    Pointer<const Object> _this = this;

    return "<" + _this->getClass()->getName() + ":" + Utility::toString((void *)*_this) + ">";
}

bool Object::isTrue() const {
    return true;
}

Pointer<Object> Object::call(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args) {
    Pointer<Object> _this = this;

    Pointer<Object> f = _this->get(name);

    if (!f)
        Esther::runtimeError("Object::call: undefined identifier '" + name + "'");

    return _this->call(esther, f, args);
}

Pointer<Object> Object::call(Esther *esther, Pointer<Object> f, const std::vector<Pointer<Object>> &args) {
    Pointer<Object> _this = this;

    if (dynamic_cast<Function *>(*f))
        return ((Function *)*f)->invoke(esther, _this, args);

    std::vector<Pointer<Object>> actualArgs;
    actualArgs.reserve(args.size() + 1);
    actualArgs << _this;
    actualArgs.insert(actualArgs.end(), args.begin(), args.end());

    return f->call(esther, "()", actualArgs);
}

Pointer<Object> Object::call(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args, Pointer<Class> expectedReturnClass) {
    Pointer<Object> _this = this;

    Pointer<Object> value = _this->call(esther, name, args);

    if (!value->is(expectedReturnClass))
        Esther::runtimeError(value->getClass()->toString() + " is not a valid return type for " + name + " (" + expectedReturnClass->getName() + " expected)");

    return value;
}

Pointer<Object> Object::callIfFound(Esther *esther, const std::string &name, const std::vector<Pointer<Object>> &args) {
    Pointer<Object> _this = this;

    Pointer<Object> f = _this->get(name);

    if (!f)
        return nullptr;

    return _this->call(esther, f, args);
}

void Object::copy(ManagedObject *dst) {
    new (dst) Object(*this);
}

int Object::getSize() const {
    return sizeof *this;
}

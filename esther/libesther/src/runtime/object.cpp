#include "object.h"

#include "runtime/class.h"
#include "runtime/esther.h"
#include "common/utility.h"
#include "runtime/function.h"

Object::Object(Ptr<Class> objectClass)
    : objectClass(objectClass)
    , attributes(nullptr) {
}

Object::~Object() {
}

Ptr<Class> Object::getClass() const {
    return objectClass;
}

void Object::setClass(Ptr<Class> objectClass) {
    this->objectClass = objectClass;
}

bool Object::hasAttribute(const std::string &name) const {
    return attributes && (attributes->find(name) != attributes->end());
}

Ptr<Object> Object::getAttribute(const std::string &name) const {
    return attributes ? attributes->at(name) : nullptr;
}

void Object::setAttribute(const std::string &name, Ptr<Object> value) {
    if (!attributes)
        attributes = new std::map<std::string, Object *>;

    (*attributes)[name] = value;
}

Ptr<Object> Object::get(const std::string &name) const {
    Ptr<const Object> _this = this;

    return _this->hasAttribute(name) ? _this->getAttribute(name) : _this->objectClass->lookup(name);
}

bool Object::is(Ptr<Class> _class) const {
    Ptr<const Object> _this = this;

    return _this->objectClass->isChild(_class);
}

std::string Object::toString() const {
    Ptr<const Object> _this = this;

    return "<" + _this->getClass()->getName() + ":" + Utility::toString((void *)*_this) + ">";
}

bool Object::isTrue() const {
    return true;
}

Ptr<Object> Object::call(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args) {
    Ptr<Object> _this = this;

    Ptr<Object> f = _this->get(name);

    if (!f)
        Esther::runtimeError("Object::call: undefined identifier '" + name + "'");

    return _this->call(esther, f, args);
}

Ptr<Object> Object::call(Esther *esther, Ptr<Object> f, const std::vector<Ptr<Object>> &args) {
    Ptr<Object> _this = this;

    if (dynamic_cast<Function *>(*f))
        return static_cast<Function *>(*f)->invoke(esther, _this, args);

    std::vector<Ptr<Object>> actualArgs;
    actualArgs.reserve(args.size() + 1);
    actualArgs << _this;
    actualArgs.insert(actualArgs.end(), args.begin(), args.end());

    return f->call(esther, "()", actualArgs);
}

Ptr<Object> Object::call(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args, Ptr<Class> expectedReturnClass) {
    Ptr<Object> _this = this;

    Ptr<Object> value = _this->call(esther, name, args);

    if (!value->is(expectedReturnClass))
        Esther::runtimeError(value->getClass()->toString() + " is not a valid return type for " + name + " (" + expectedReturnClass->getName() + " expected)");

    return value;
}

Ptr<Object> Object::callIfFound(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args) {
    Ptr<Object> _this = this;

    Ptr<Object> f = _this->get(name);

    if (!f)
        return nullptr;

    return _this->call(esther, f, args);
}

void Object::finalize() {
    delete attributes;
}

void Object::mapOnReferences(void (*f)(ManagedObject *&)) {
    f(reinterpret_cast<ManagedObject *&>(objectClass));

    if (attributes)
        for (auto &attr : *attributes)
            f(reinterpret_cast<ManagedObject *&>(attr.second));
}

int Object::getSize() const {
    return sizeof *this;
}

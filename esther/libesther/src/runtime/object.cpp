#include "runtime/object.h"

#include "runtime/class.h"
#include "esther.h"
#include "common/utility.h"
#include "runtime/function.h"
#include "collections/sherwoodmap.h"
#include "collections/hashmap.h"

namespace es {

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

bool Object::hasAttribute(Esther *esther, const std::string &name) const {
    Ptr<const Object> _this = this;

    uint32_t id = esther->id(name);
    return _this->attributes && (_this->attributes->contains(id));
}

Ptr<Object> Object::getAttribute(Esther *esther, const std::string &name) const {
    Ptr<const Object> _this = this;

    uint32_t id = esther->id(name);
    return _this->attributes ? _this->attributes->get(id) : nullptr;
}

void Object::setAttribute(Esther *esther, const std::string &name, Ptr<Object> value) {
    Ptr<Object> _this = this;

    if (!_this->attributes)
        _this->attributes = new SherwoodMap<uint32_t, Object *>;

    uint32_t id = esther->id(name);
    _this->attributes->put(id, value);
}

Ptr<Object> Object::get(Esther *esther, const std::string &name) const {
    Ptr<const Object> _this = this;

    return _this->hasAttribute(esther, name) ? _this->getAttribute(esther, name) : _this->objectClass->lookup(esther, name);
}

bool Object::is(Ptr<Class> _class) const {
    Ptr<const Object> _this = this;

    return _this->objectClass->isChild(_class);
}

std::string Object::toString() const {
    Ptr<const Object> _this = this;

    return "<" + _this->getClass()->getName() + ":" + Utility::toString(_this) + ">";
}

bool Object::isTrue() const {
    return true;
}

Ptr<Object> Object::call(Esther *esther, const std::string &name, const std::vector<Ptr<Object>> &args) {
    Ptr<Object> _this = this;

    Ptr<Object> f = _this->get(esther, name);

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

    Ptr<Object> f = _this->get(esther, name);

    if (!f)
        return nullptr;

    return _this->call(esther, f, args);
}

bool Object::equals(Ptr<Object> object) const {
    return this == object;
}

uint32_t Object::hash() const {
    return reinterpret_cast<uint32_t>(this);
}

void Object::finalize() {
    // delete attributes;
}

void Object::mapOnReferences(void (*f)(ManagedObject *&)) {
    f(reinterpret_cast<ManagedObject *&>(objectClass));

    // if (attributes)
    //     for (auto &attr : *attributes)
    //         f(reinterpret_cast<ManagedObject *&>(attr.second));

    if (attributes)
        f(reinterpret_cast<ManagedObject *&>(attributes));
}

int Object::getSize() const {
    return sizeof *this;
}
}

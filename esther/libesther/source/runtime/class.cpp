#include "class.h"

#include "esther.h"
#include "classclass.h"

Class::Class(Esther *esther, const std::string &name, Pointer<Class> superclass)
    : Object(*esther->getClassClass())
    , name(new std::string(name))
    , superclass(superclass) {
}

Class::~Class() {
    delete name;
}

std::string Class::getName() const {
    return *name;
}

void Class::setName(const std::string &name) {
    *this->name = name;
}

Pointer<Class> Class::getSuperclass() const {
    return superclass;
}

void Class::setSuperclass(Pointer<Class> superclass) {
    this->superclass = superclass;
}

Pointer<Object> Class::get(const std::string &name) const {
    Pointer<const Class> _this = this;

    Pointer<Object> temp = nullptr;
    return (temp = _this->Object::get(name)) ? temp : _this->superclass ? _this->superclass->lookup(name) : nullptr;
}

Pointer<Object> Class::newInstance(Esther *esther, const std::vector<Pointer<Object>> &args) {
    Pointer<Class> _this = this;

    Pointer<Object> instance = _this->createNewInstance(esther, args);
    instance->callIfFound(esther, "initialize", args);
    return instance;
}

bool Class::isChild(Pointer<Class> _class) const {
    Pointer<const Class> _this = this;

    return _this == _class || (_this->superclass && _this->superclass->isChild(_class));
}

std::string Class::toString() const {
    Pointer<const Class> _this = this;

    return _this->getName().empty() ? "<anonymous class>" : "<class " + _this->getName() + ">";
}

Pointer<Object> Class::lookup(const std::string &name) const {
    Pointer<const Class> _this = this;

    return _this->hasAttribute(name) ? _this->getAttribute(name) : _this->superclass ? _this->superclass->lookup(name) : nullptr;
}

void Class::copy(ManagedObject *dst) {
    new (dst) Class(*this);
}

int Class::getSize() const {
    return sizeof *this;
}

Pointer<Object> Class::createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &args) {
    Pointer<Class> _this = this;

    Pointer<Object> instance = _this->superclass->createNewInstance(esther, args);
    instance->setClass(_this);
    return instance;
}

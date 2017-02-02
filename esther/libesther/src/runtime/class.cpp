#include "class.h"

#include "runtime/esther.h"
#include "runtime/rootclass/classclass.h"

Class::Class(Esther *esther, const std::string &name, Ptr<Class> superclass)
    : Object(*esther->getClassClass())
    , name(new std::string(name))
    , superclass(superclass) {
}

std::string Class::getName() const {
    return *name;
}

void Class::setName(const std::string &name) {
    *this->name = name;
}

Ptr<Class> Class::getSuperclass() const {
    return superclass;
}

void Class::setSuperclass(Ptr<Class> superclass) {
    this->superclass = superclass;
}

Ptr<Object> Class::get(const std::string &name) const {
    Ptr<const Class> _this = this;

    Ptr<Object> temp = nullptr;
    return (temp = _this->Object::get(name)) ? temp : _this->superclass ? _this->superclass->lookup(name) : nullptr;
}

Ptr<Object> Class::newInstance(Esther *esther, const std::vector<Ptr<Object>> &args) {
    Ptr<Class> _this = this;

    Ptr<Object> instance = _this->createNewInstance(esther, args);
    instance->callIfFound(esther, "initialize", args);
    return instance;
}

bool Class::isChild(Ptr<Class> _class) const {
    Ptr<const Class> _this = this;

    return _this == _class || (_this->superclass && _this->superclass->isChild(_class));
}

std::string Class::toString() const {
    Ptr<const Class> _this = this;

    return _this->getName().empty() ? "<anonymous class>" : "<class " + _this->getName() + ">";
}

Ptr<Object> Class::lookup(const std::string &name) const {
    Ptr<const Class> _this = this;

    return _this->hasAttribute(name) ? _this->getAttribute(name) : _this->superclass ? _this->superclass->lookup(name) : nullptr;
}

void Class::finalize() {
    Object::finalize();

    delete name;
}

void Class::mapOnReferences(const std::function<void(ManagedObject *&)> &f) {
    Object::mapOnReferences(f);

    if (superclass)
        f(reinterpret_cast<ManagedObject *&>(superclass));
}

int Class::getSize() const {
    return sizeof *this;
}

Ptr<Object> Class::createNewInstance(Esther *esther, const std::vector<Ptr<Object>> &args) {
    Ptr<Class> _this = this;

    Ptr<Object> instance = _this->superclass->createNewInstance(esther, args);
    instance->setClass(_this);
    return instance;
}

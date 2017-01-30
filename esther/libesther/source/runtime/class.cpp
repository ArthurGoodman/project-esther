#include "class.h"

std::string Class::getName() const {
    return name;
}

void Class::setName(const std::string &name) {
    this->name = name;
}

Pointer<Class> Class::getSuperclass() const {
    return superclass;
}

void Class::setSuperclass(Pointer<Class> superclass) {
    this->superclass = superclass;
}

Pointer<Object> Class::get(const std::string &name) const {
    Pointer<Object> temp = nullptr;
    return (temp = Object::get(name)) ? temp : superclass ? superclass->lookup(name) : nullptr;
}

Pointer<Object> Class::newInstance(Esther *esther, const std::vector<Pointer<Object>> &args) {
    Pointer<Object> instance = createNewInstance(args);
    instance->callIfFound(esther, "initialize", args);
    return instance;
}

bool Class::isChild(Pointer<Class> _class) const {
    return this == _class || (superclass && superclass->isChild(_class));
}

std::string Class::toString() const {
    return getName().empty() ? "<anonymous class>" : "<class " + getName() + ">";
}

Pointer<Object> Class::lookup(const std::string &name) const {
    return hasAttribute(name) ? getAttribute(name) : superclass ? superclass->lookup(name) : nullptr;
}

Class::Class(Pointer<Class> classClass, const std::string &name, Pointer<Class> superclass)
    : Object(classClass)
    , name(name)
    , superclass(superclass) {
}

Pointer<Object> Class::createNewInstance(const std::vector<Pointer<Object>> &args) {
    Pointer<Object> instance = superclass->createNewInstance(args);
    instance->setClass(this);
    return instance;
}

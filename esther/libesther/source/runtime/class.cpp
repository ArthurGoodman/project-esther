#include "class.h"

std::string Class::getName() const {
    return name;
}

void Class::setName(const std::string &name) {
    this->name = name;
}

Class *Class::getSuperclass() const {
    return superclass;
}

void Class::setSuperclass(Class *superclass) {
    this->superclass = superclass;
}

Object *Class::get(const std::string &name) const {
    Object *temp = nullptr;
    return (temp = Object::get(name)) ? temp : superclass ? superclass->lookup(name) : nullptr;
}

Object *Class::newInstance(const std::vector<Object *> &args) {
    Object *instance = createNewInstance(args);
    instance->callIfFound("initialize", args);
    return instance;
}

bool Class::isChild(Class *_class) const {
    return this == _class || (superclass && superclass->isChild(_class));
}

std::string Class::toString() const {
    return getName().empty() ? "<anonymous class>" : "<class " + getName() + ">";
}

Object *Class::lookup(const std::string &name) const {
    return hasAttribute(name) ? getAttribute(name) : superclass ? superclass->lookup(name) : nullptr;
}

Class::Class(Class *classClass, const std::string &name, Class *superclass)
    : Object(classClass), name(name), superclass(superclass) {
}

Object *Class::createNewInstance(const std::vector<Object *> &args) {
    Object *instance = superclass->createNewInstance(args);
    instance->setClass(this);
    return instance;
}

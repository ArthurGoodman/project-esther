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

Object *Class::newInstance() {
    return createNewInstance();
}

std::string Class::toString() const {
    return getName().empty() ? "<anonymous class>" : "<class " + getName() + ">";
}

Object *Class::createNewInstance() {
    return new Object(this);
}

Class::Class(Class *objectClass, const std::string &name, Class *superclass)
    : Object(objectClass), name(name), superclass(superclass) {
}

#include "runtime/class.h"

#include "esther.h"
#include "runtime/rootclass/classclass.h"

namespace es {

Class::Class(Esther *esther, const std::string &name, Class *superclass)
    : Object(esther->getClassClass())
    , name(name)
    , superclass(superclass) {
}

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

Object *Class::newInstance(Esther *esther, const std::vector<Object *> &args) {
    Object *instance = createNewInstance(esther, args);
    instance->callIfFound(esther, "initialize", args);
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

void Class::finalize() {
    Object::finalize();

    name.~basic_string();
}

void Class::mapOnReferences(void (*f)(ManagedObject *&)) {
    Object::mapOnReferences(f);

    if (superclass)
        f(reinterpret_cast<ManagedObject *&>(superclass));
}

Object *Class::createNewInstance(Esther *esther, const std::vector<Object *> &args) {
    Object *instance = superclass->createNewInstance(esther, args);
    instance->setClass(this);
    return instance;
}
}

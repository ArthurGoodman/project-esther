#include "class.h"

#include "esther.h"

namespace esther {

Class::Class(string name, Class *superclass)
    : Object("Class"), name(name), superclass(superclass) {
}

Class::Class(string name, string superclassName)
    : Object("Class"), name(name), superclass(superclassName.empty() ? Esther::getObjectClass() : Esther::getRootClass(superclassName)) {
}

string Class::getName() {
    return name;
}

Class *Class::getSuperclass() {
    return superclass;
}

void Class::setSuperclass(Class *superclass) {
    this->superclass = superclass;
}

bool Class::isChild(Class *_class) {
    return false;
}

Object *Class::newInstance() {
    return new Object(this);
}

bool Class::hasMethod(string name) {
    return methods.find(name) != methods.end();
}

Method *Class::getMethod(string name) {
    return hasMethod(name) ? methods.at(name) : 0;
}

void Class::setMethod(string name, Method *method) {
}

Method *Class::lookup(string name) {
    if (hasMethod(name))
        return getMethod(name);

    if (superclass)
        return superclass->lookup(name);

    return 0;
}

Object *Class::call(string name, list<Object *> args) {
    return Esther::getNull();
}

Object *Class::call(string name, Object *arg) {
    return call(name, list<Object *>(1, arg));
}

Object *Class::call(string name) {
    return call(name, list<Object *>());
}

string Class::toString() {
    return name.empty() ? "<Anonymous Class>" : name;
}
}

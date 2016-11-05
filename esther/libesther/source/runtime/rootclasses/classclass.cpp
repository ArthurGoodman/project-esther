#include "classclass.h"

Class *ClassClass::createClass(const std::string &name, Class *superclass) {
    return new Class(this, name, superclass ? superclass : getSuperclass());
}

Object *ClassClass::createNewInstance() {
    return createClass("");
}

ClassClass::ClassClass()
    : Class("Class") {
}

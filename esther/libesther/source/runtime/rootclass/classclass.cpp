#include "classclass.h"

Class *ClassClass::createClass(const std::string &name, Class *superclass) {
    return new Class(this, name, superclass ? superclass : getSuperclass());
}

Object *ClassClass::createNewInstance() {
    return createClass("");
}

void ClassClass::setupMethods() {
    def("new", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return ((Class *)self)->newInstance();
    });
}

ClassClass::ClassClass(Runtime *runtime)
    : RootClass(runtime, "Class", nullptr) {
}

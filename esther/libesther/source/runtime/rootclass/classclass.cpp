#include "classclass.h"

#include "runtime.h"

Class *ClassClass::createClass(const std::string &name, Class *superclass) {
    return new Class(this, name, superclass ? superclass : getSuperclass());
}

Object *ClassClass::createNewInstance(const std::vector<Object *> &) {
    return createClass("");
}

void ClassClass::setupMethods() {
    def("new", [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return ((Class *)self)->newInstance(args);
    });

    def("superclass", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return ((Class *)self)->getSuperclass() ? ((Class *)self)->getSuperclass() : runtime->getNull();
    });
}

ClassClass::ClassClass(Runtime *runtime)
    : RootClass(runtime, "Class", nullptr) {
}

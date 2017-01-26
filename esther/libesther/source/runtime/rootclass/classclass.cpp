#include "classclass.h"

#include "esther.h"

Class *ClassClass::createClass(const std::string &name, Class *superclass) {
    return new Class(this, name, superclass ? superclass : getSuperclass());
}

Object *ClassClass::createNewInstance(const std::vector<Object *> &) {
    return createClass("");
}

void ClassClass::setupMethods() {
    defFunc("new", -1, [=](Object *self, const std::vector<Object *> &args) -> Object * {
        return ((Class *)self)->newInstance(args);
    });

    defFunc("superclass", [=](Object *self, const std::vector<Object *> &) -> Object * {
        return ((Class *)self)->getSuperclass() ? ((Class *)self)->getSuperclass() : esther->getNull();
    });
}

ClassClass::ClassClass(Esther *e)
    : RootClass(e, "Class", nullptr) {
}

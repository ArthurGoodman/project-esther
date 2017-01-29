#include "classclass.h"

#include "esther.h"

Class *ClassClass::createClass(const std::string &name, Class *superclass) {
    return new Class(this, name, superclass ? superclass : getSuperclass());
}

Object *ClassClass::createNewInstance(const std::vector<Object *> &) {
    return createClass("");
}

void ClassClass::setupMethods(Esther *esther) {
    defFunc(esther, "new", -1, [=](Esther *esther, Object *self, const std::vector<Object *> &args) -> Object * {
        return ((Class *)self)->newInstance(esther, args);
    });

    defFunc(esther, "superclass", [=](Esther *esther, Object *self, const std::vector<Object *> &) -> Object * {
        return ((Class *)self)->getSuperclass() ? ((Class *)self)->getSuperclass() : esther->getNull();
    });
}

ClassClass::ClassClass(Esther *esther)
    : RootClass(esther, "Class", nullptr) {
}

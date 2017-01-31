#include "classclass.h"

#include "esther.h"

Pointer<Class> ClassClass::createClass(const std::string &name, Pointer<Class> superclass) {
    return new Class(this, name, superclass ? superclass : getSuperclass());
}

Pointer<Object> ClassClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    return *createClass("");
}

void ClassClass::setupMethods(Esther *esther) {
    defFunc(esther, "new", -1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return ((Class *)*self)->newInstance(esther, args);
    });

    defFunc(esther, "superclass", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return ((Class *)*self)->getSuperclass() ? ((Class *)*self)->getSuperclass() : esther->getNull();
    });
}

ClassClass::ClassClass(Esther *esther)
    : RootClass(esther, "Class", nullptr) {
}

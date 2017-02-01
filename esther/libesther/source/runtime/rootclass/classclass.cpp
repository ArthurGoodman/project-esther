#include "classclass.h"

#include "esther.h"

ClassClass::ClassClass(Esther *esther)
    : RootClass(esther, "Class", nullptr) {
}

void ClassClass::setupMethods(Esther *esther) {
    Pointer<ClassClass> _this = this;

    _this->defFunc(esther, "new", -1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return ((Class *)*self)->newInstance(esther, args);
    });

    _this->defFunc(esther, "superclass", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return ((Class *)*self)->getSuperclass() ? ((Class *)*self)->getSuperclass() : esther->getNull();
    });
}

Pointer<Object> ClassClass::createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &) {
    return new Class(esther, "", esther->getObjectClass());
}

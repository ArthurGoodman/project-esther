#include "classclass.h"

#include "esther.h"

ClassClass::ClassClass(Esther *esther)
    : RootClass(esther, "Class", nullptr) {
}

void ClassClass::setupMethods(Esther *esther) {
    defFunc(esther, "new", -1, [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &args) -> Pointer<Object> {
        return ((Class *)*self)->newInstance(esther, args);
    });

    defFunc(esther, "superclass", [](Esther *esther, Pointer<Object> self, const std::vector<Pointer<Object>> &) -> Pointer<Object> {
        return ((Class *)*self)->getSuperclass() ? ((Class *)*self)->getSuperclass() : esther->getNull();
    });
}

void ClassClass::copy(ManagedObject *dst) {
    new (dst) ClassClass(*this);
}

Pointer<Object> ClassClass::createNewInstance(Esther *esther, const std::vector<Pointer<Object>> &) {
    return new Class(esther, "", esther->getObjectClass());
}

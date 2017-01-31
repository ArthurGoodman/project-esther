#include "booleanclass.h"

#include "esther.h"

void BooleanClass::copy(ManagedObject *dst) {
    new (dst) BooleanClass(*this);
}

Pointer<Object> BooleanClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    Esther::runtimeError("cannot create new instance of Boolean class");
    return nullptr;
}

void BooleanClass::setupMethods(Esther *) {
}

BooleanClass::BooleanClass(Esther *esther)
    : RootClass(esther, "Boolean", esther->getObjectClass()) {
}

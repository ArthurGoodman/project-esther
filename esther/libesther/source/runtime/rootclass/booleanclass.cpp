#include "booleanclass.h"

#include "esther.h"

BooleanClass::BooleanClass(Esther *esther)
    : RootClass(esther, "Boolean", esther->getObjectClass()) {
}

void BooleanClass::setupMethods(Esther *) {
}

void BooleanClass::copy(ManagedObject *dst) {
    new (dst) BooleanClass(*this);
}

Pointer<Object> BooleanClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    Esther::runtimeError("cannot create new instance of Boolean class");
    return nullptr;
}

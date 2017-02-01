#include "nullclass.h"

#include "null.h"
#include "esther.h"

NullClass::NullClass(Esther *esther)
    : RootClass(esther, "Null", esther->getObjectClass()) {
}

void NullClass::setupMethods(Esther *) {
}

void NullClass::copy(ManagedObject *dst) {
    new (dst) NullClass(*this);
}

Pointer<Object> NullClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    Esther::runtimeError("cannot create new instance of Null class");
    return nullptr;
}

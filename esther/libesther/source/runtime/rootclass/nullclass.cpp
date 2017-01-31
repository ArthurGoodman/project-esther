#include "nullclass.h"

#include "null.h"
#include "esther.h"

void NullClass::copy(ManagedObject *dst) {
    new (dst) NullClass(*this);
}

Pointer<Object> NullClass::createNewInstance(const std::vector<Pointer<Object>> &) {
    Esther::runtimeError("cannot create new instance of Null class");
    return nullptr;
}

void NullClass::setupMethods(Esther *) {
}

NullClass::NullClass(Esther *esther)
    : RootClass(esther, "Null", esther->getObjectClass()) {
}

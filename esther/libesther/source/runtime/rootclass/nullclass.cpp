#include "nullclass.h"

#include "null.h"
#include "esther.h"

NullClass::NullClass(Esther *esther)
    : RootClass(esther, "Null", esther->getObjectClass()) {
}

void NullClass::setupMethods(Esther *) {
}

Pointer<Object> NullClass::createNewInstance(Esther *, const std::vector<Pointer<Object>> &) {
    Esther::runtimeError("cannot create new instance of Null class");
    return nullptr;
}

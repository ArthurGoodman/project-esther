#include "nullclass.h"

#include "runtime/null.h"
#include "runtime/esther.h"

NullClass::NullClass(Esther *esther)
    : RootClass(esther, "Null", esther->getObjectClass()) {
}

void NullClass::setupMethods(Esther *) {
}

Ptr<Object> NullClass::createNewInstance(Esther *, const std::vector<Ptr<Object>> &) {
    Esther::runtimeError("cannot create new instance of Null class");
    return nullptr;
}
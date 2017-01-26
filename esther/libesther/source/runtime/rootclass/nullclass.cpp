#include "nullclass.h"

#include "null.h"
#include "esther.h"

Object *NullClass::createNewInstance(const std::vector<Object *> &) {
    Esther::runtimeError("cannot create new instance of Null class");
    return nullptr;
}

void NullClass::setupMethods() {
}

NullClass::NullClass(Esther *e)
    : RootClass(e, "Null", e->getObjectClass()) {
}

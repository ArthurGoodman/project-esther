#include "runtime/rootclass/booleanclass.h"

#include "esther.h"

namespace es {

BooleanClass::BooleanClass(Esther *esther)
    : RootClass(esther, "Boolean", esther->getObjectClass()) {
}

void BooleanClass::setupMethods(Esther *) {
}

Object *BooleanClass::createNewInstance(Esther *, const std::vector<Object *> &) {
    Esther::runtimeError("cannot create new instance of Boolean class");
    return nullptr;
}
}

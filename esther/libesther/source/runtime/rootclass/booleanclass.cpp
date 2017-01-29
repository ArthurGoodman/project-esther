#include "booleanclass.h"

#include "esther.h"

Object *BooleanClass::createNewInstance(const std::vector<Object *> &) {
    Esther::runtimeError("cannot create new instance of Boolean class");
    return nullptr;
}

void BooleanClass::setupMethods(Esther *) {
}

BooleanClass::BooleanClass(Esther *esther)
    : RootClass(esther, "Boolean", esther->getObjectClass()) {
}

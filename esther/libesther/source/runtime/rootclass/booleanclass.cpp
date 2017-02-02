#include "booleanclass.h"

#include "esther.h"

BooleanClass::BooleanClass(Esther *esther)
    : RootClass(esther, "Boolean", esther->getObjectClass()) {
}

void BooleanClass::setupMethods(Esther *) {
}

Ptr<Object> BooleanClass::createNewInstance(Esther *, const std::vector<Ptr<Object>> &) {
    Esther::runtimeError("cannot create new instance of Boolean class");
    return nullptr;
}

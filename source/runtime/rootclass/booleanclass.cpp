#include "booleanclass.h"

#include "runtime.h"

BooleanClass::BooleanClass()
    : RootClass("Boolean") {
}

void BooleanClass::setupMethods() {
}

Object *BooleanClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Boolean class");
    return 0;
}

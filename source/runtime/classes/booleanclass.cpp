#include "booleanclass.h"

#include "runtime.h"

BooleanClass::BooleanClass()
    : RootClass("Boolean") {
}

Object *BooleanClass::newInstance() {
    Runtime::runtimeError("cannot create new instance of Boolean class");
    return 0;
}

void BooleanClass::setupMethods() {
}

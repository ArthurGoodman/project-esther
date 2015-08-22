#include "nullclass.h"

#include "runtime.h"

NullClass::NullClass()
    : RootClass("Null") {
}

void NullClass::setupMethods() {
}

Object *NullClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Null class");
    return 0;
}

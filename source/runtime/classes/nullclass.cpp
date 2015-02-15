#include "nullclass.h"

#include "runtime.h"

NullClass::NullClass()
    : RootClass("Null") {
}

Object *NullClass::newInstance() {
    Runtime::runtimeError("cannot create new instance of Null class");
    return 0;
}

void NullClass::setupMethods() {
}

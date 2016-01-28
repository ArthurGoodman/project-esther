#include "nullclass.h"

#include "runtime.h"
#include "signature.h"
#include "string.h"

NullClass::NullClass()
    : RootClass("Null") {
}

void NullClass::setupMethods() {
}

IObject *NullClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Null class");
    return 0;
}

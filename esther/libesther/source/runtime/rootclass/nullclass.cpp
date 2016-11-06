#include "nullclass.h"

#include "null.h"
#include "runtime.h"

Object *NullClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Null class");
    return nullptr;
}

void NullClass::setupMethods() {
}

NullClass::NullClass(Runtime *runtime)
    : RootClass(runtime, "Null", runtime->getObjectClass()) {
}

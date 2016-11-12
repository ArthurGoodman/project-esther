#include "booleanclass.h"

#include "runtime.h"

Object *BooleanClass::createNewInstance(const std::vector<Object *> &) {
    Runtime::runtimeError("cannot create new instance of Boolean class");
    return nullptr;
}

void BooleanClass::setupMethods() {
}

BooleanClass::BooleanClass(Runtime *runtime)
    : RootClass(runtime, "Boolean", runtime->getObjectClass()) {
}

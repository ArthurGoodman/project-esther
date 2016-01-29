#include "booleanclass.h"

#include "runtime.h"
#include "string.h"
#include "variant.h"
#include "signature.h"

BooleanClass::BooleanClass()
    : RootClass("Boolean") {
}

void BooleanClass::setupMethods() {
}

IObject *BooleanClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Boolean class");
    return 0;
}

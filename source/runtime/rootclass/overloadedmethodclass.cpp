#include "overloadedmethodclass.h"

#include "overloadedmethod.h"
#include "runtime.h"

OverloadedMethodClass::OverloadedMethodClass()
    : RootClass("OverloadedMethod", "Method") {
}

void OverloadedMethodClass::setupMethods() {
}

IObject *OverloadedMethodClass::createNewInstance() {
    return new OverloadedMethod("", Runtime::getObjectClass(), false);
}

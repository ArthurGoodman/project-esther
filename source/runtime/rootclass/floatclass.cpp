#include "floatclass.h"

#include "runtime.h"
#include "float.h"

FloatClass::FloatClass()
    : RootClass("Float") {
}

Object *FloatClass::newInstance() {
    return new Float;
}

void FloatClass::setupMethods() {
}

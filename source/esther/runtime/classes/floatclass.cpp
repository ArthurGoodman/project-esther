#include "floatclass.h"

#include "runtime.h"
#include "float.h"

namespace esther {

FloatClass::FloatClass()
    : Class("Float") {
    Runtime::setRootClass(this);
}

Object *FloatClass::newInstance() {
    return new Float;
}

void FloatClass::setupMethods() {
}
}

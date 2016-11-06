#include "floatclass.h"

#include "valueobject.h"
#include "runtime.h"

ValueObject *FloatClass::createFloat(double value) {
    return new ValueObject(this, value);
}

Object *FloatClass::createNewInstance() {
    return createFloat(0.0);
}

void FloatClass::setupMethods() {
}

FloatClass::FloatClass(Runtime *runtime)
    : RootClass(runtime, "Float", runtime->getObjectClass()) {
}

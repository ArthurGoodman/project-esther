#include "floatclass.h"

#include "valueobject.h"
#include "runtime.h"
#include "numericclass.h"

ValueObject *FloatClass::createFloat(double value) {
    return new ValueObject(this, value);
}

Object *FloatClass::createNewInstance(const std::vector<Object *> &) {
    return createFloat(0.0);
}

void FloatClass::setupMethods() {
}

FloatClass::FloatClass(Runtime *runtime)
    : RootClass(runtime, "Float", runtime->getNumericClass()) {
}

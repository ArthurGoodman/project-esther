#include "floatclass.h"

#include "valueobject.h"

Object *FloatClass::createFloat(double value) {
    return new ValueObject(this, value);
}

void FloatClass::setupMethods() {
}

Object *FloatClass::createNewInstance() {
    return createFloat(0.0);
}

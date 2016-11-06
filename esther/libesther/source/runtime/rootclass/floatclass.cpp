#include "floatclass.h"

#include "valueobject.h"

ValueObject *FloatClass::createFloat(double value) {
    return new ValueObject(this, value);
}

Object *FloatClass::createNewInstance() {
    return createFloat(0.0);
}

void FloatClass::setupMethods() {
}

FloatClass::FloatClass(Runtime *runtime, Class *objectClass)
    : RootClass(runtime, objectClass, "Float", objectClass->getSuperclass()) {
}

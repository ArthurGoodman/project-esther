#include "floatclass.h"

#include "valueobject.h"

ValueObject *FloatClass::createFloat(double value) {
    return new ValueObject(this, value);
}

Object *FloatClass::createNewInstance() {
    return createFloat(0.0);
}

FloatClass::FloatClass(Class *objectClass)
    : Class(objectClass, "Float", objectClass->getSuperclass()) {
}

#include "integerclass.h"

#include "valueobject.h"

ValueObject *IntegerClass::createInteger(int value) {
    return new ValueObject(this, value);
}

Object *IntegerClass::createNewInstance() {
    return createInteger(0);
}

IntegerClass::IntegerClass(Class *objectClass)
    : Class(objectClass, "Integer", objectClass->getSuperclass()) {
}

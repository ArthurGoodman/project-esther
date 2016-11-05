#include "booleanclass.h"

#include "runtime.h"

Object *BooleanClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Boolean class");
    return nullptr;
}

BooleanClass::BooleanClass(Class *objectClass)
    : Class(objectClass, "Boolean", objectClass->getSuperclass()) {
}

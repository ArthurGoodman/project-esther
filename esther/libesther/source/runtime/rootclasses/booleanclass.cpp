#include "booleanclass.h"

#include "true.h"
#include "false.h"
#include "runtime.h"

Object *BooleanClass::createTrue() {
    return new True(this);
}

Object *BooleanClass::createFalse() {
    return new False(this);
}

Object *BooleanClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Boolean class");
    return nullptr;
}

BooleanClass::BooleanClass(Class *objectClass)
    : Class(objectClass, "Boolean", objectClass->getSuperclass()) {
}

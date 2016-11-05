#include "nullclass.h"

#include "null.h"
#include "runtime.h"

Object *NullClass::createNull() {
    return new Null(this);
}

Object *NullClass::createNewInstance() {
    Runtime::runtimeError("cannot create new instance of Null class");
    return nullptr;
}

NullClass::NullClass(Class *objectClass)
    : Class(objectClass, "Null", objectClass->getSuperclass()) {
}

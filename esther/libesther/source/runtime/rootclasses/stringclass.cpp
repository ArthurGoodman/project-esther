#include "stringclass.h"

#include "valueobject.h"

ValueObject *StringClass::createString(const std::string &value) {
    return new ValueObject(this, value);
}

Object *StringClass::createNewInstance() {
    return createString("");
}

StringClass::StringClass(Class *objectClass)
    : Class(objectClass, "String", objectClass->getSuperclass()) {
}

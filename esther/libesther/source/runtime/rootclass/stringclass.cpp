#include "stringclass.h"

#include "valueobject.h"

ValueObject *StringClass::createString(const std::string &value) {
    return new ValueObject(this, value);
}

Object *StringClass::createNewInstance() {
    return createString("");
}

void StringClass::setupMethods() {
}

StringClass::StringClass(Runtime *runtime, Class *objectClass)
    : RootClass(runtime, objectClass, "String", objectClass->getSuperclass()) {
}

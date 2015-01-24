#include "object.h"

#include "class.h"
#include "io.h"

namespace esther {

Object::Object(Class *objectClass)
    : objectClass(objectClass) {
}

Class *Object::getClass() {
    return objectClass;
}

string Object::toString() {
    return "<" + objectClass->toString() + "0x" + ::toString((int)this, 16) + ">";
}
}

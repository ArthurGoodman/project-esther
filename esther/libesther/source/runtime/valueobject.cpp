#include "valueobject.h"

Variant ValueObject::getVariant() {
    return value;
}

std::string ValueObject::toString() const {
    return value.toString();
}

ValueObject::ValueObject(Class *objectClass, const Variant &value)
    : Object(objectClass), value(value) {
}

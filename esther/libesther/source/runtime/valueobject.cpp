#include "valueobject.h"

Variant ValueObject::getVariant() const {
    return value;
}

void ValueObject::setVariant(const Variant &value) {
    this->value = value;
}

std::string ValueObject::toString() const {
    return value.toString();
}

ValueObject::ValueObject(Class *objectClass, const Variant &value)
    : Object(objectClass), value(value) {
}

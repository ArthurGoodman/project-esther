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

int ValueObject::getSize() const {
    return sizeof *this;
}

ValueObject::ValueObject(Pointer<Class> objectClass, const Variant &value)
    : Object(objectClass)
    , value(value) {
}

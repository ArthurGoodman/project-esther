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

void ValueObject::copy(ManagedObject *dst) {
    new (dst) ValueObject(*this);
}

int ValueObject::getSize() const {
    return sizeof *this;
}

ValueObject::ValueObject(Pointer<Class> objectClass, const Variant &value)
    : Object(objectClass)
    , value(value) {
}

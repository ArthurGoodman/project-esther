#include "runtime/valueobject.h"

#include "esther.h"

namespace es {

ValueObject::ValueObject(Esther *esther, const Variant &value)
    : Object(variantTypeToObjectClass(esther, value.getType()))
    , value(value) {
    setSize(sizeof *this);
}

Variant ValueObject::getVariant() const {
    return value;
}

void ValueObject::setVariant(const Variant &value) {
    this->value = value;
}

std::string ValueObject::toString() const {
    return value.toString();
}

Class *ValueObject::variantTypeToObjectClass(Esther *esther, Variant::Type type) {
    switch (type) {
    case Variant::Char:
        return esther->getRootClass("Character");

    case Variant::Integer:
        return esther->getRootClass("Integer");

    case Variant::Real:
        return esther->getRootClass("Float");

    case Variant::String:
        return esther->getRootClass("String");

    default:
        return nullptr;
    }
}
}

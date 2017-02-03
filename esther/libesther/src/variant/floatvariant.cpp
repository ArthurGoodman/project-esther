#include "variant/floatvariant.h"

#include "common/utility.h"

#if HEAP_VARIANT

namespace es {

FloatVariant::FloatVariant(double value)
    : value(value) {
}

VariantPrivate *FloatVariant::clone() const {
    return new FloatVariant(value);
}

Variant::Type FloatVariant::type() const {
    return Variant::Real;
}

int FloatVariant::toInteger() const {
    return value;
}

double FloatVariant::toReal() const {
    return value;
}

char FloatVariant::toChar() const {
    return value;
}

std::string FloatVariant::toString() const {
    return Utility::toString(value);
}
}

#endif

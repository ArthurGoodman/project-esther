#include "variant/integervariant.h"

#include "common/utility.h"

#ifdef HEAP_VARIANT

namespace es {

IntegerVariant::IntegerVariant(int value)
    : value(value) {
}

VariantPrivate *IntegerVariant::clone() const {
    return new IntegerVariant(value);
}

Variant::Type IntegerVariant::type() const {
    return Variant::Integer;
}

int IntegerVariant::toInteger() const {
    return value;
}

double IntegerVariant::toReal() const {
    return value;
}

char IntegerVariant::toChar() const {
    return value;
}

std::string IntegerVariant::toString() const {
    return Utility::toString(value);
}
}

#endif

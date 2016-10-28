#include "stringvariant.h"

#if HEAP_VARIANT

#include "utility.h"

StringVariant::StringVariant(const std::string &value)
    : value(value) {
}

VariantPrivate *StringVariant::clone() const {
    return new StringVariant(value);
}

Variant::Type StringVariant::type() const {
    return Variant::String;
}

int StringVariant::toInteger() const {
    return Utility::fromString<int>(value);
}

double StringVariant::toReal() const {
    return Utility::fromString<double>(value);
}

char StringVariant::toChar() const {
    return Utility::fromString<char>(value);
}

std::string StringVariant::toString() const {
    return value;
}

#endif

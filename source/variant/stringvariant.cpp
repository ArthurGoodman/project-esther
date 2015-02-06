#include "stringvariant.h"

#include "utility.h"

StringVariant::StringVariant(string value)
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

double StringVariant::toFloat() const {
    return Utility::fromString<double>(value);
}

char StringVariant::toChar() const {
    return Utility::fromString<char>(value);
}

string StringVariant::toString() const {
    return value;
}

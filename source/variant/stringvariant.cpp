#include "stringvariant.h"

StringVariant::StringVariant(string value) : value(value) {}

VariantPrivate *StringVariant::clone() const { return new StringVariant(value); }

Variant::Type StringVariant::type() const { return Variant::String; }

int StringVariant::toInteger() const { return ::fromString<int>(value); }
double StringVariant::toFloat() const { return ::fromString<double>(value); }
char StringVariant::toChar() const { return ::fromString<char>(value); }
string StringVariant::toString() const { return value; }

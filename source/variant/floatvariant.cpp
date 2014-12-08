#include "floatvariant.h"

FloatVariant::FloatVariant(double value)
    : value(value) {
}

VariantPrivate *FloatVariant::clone() const {
    return new FloatVariant(value);
}

Variant::Type FloatVariant::type() const {
    return Variant::Float;
}

int FloatVariant::toInteger() const {
    return value;
}

double FloatVariant::toFloat() const {
    return value;
}

char FloatVariant::toChar() const {
    return value;
}

string FloatVariant::toString() const {
    return ::toString<double>(value);
}

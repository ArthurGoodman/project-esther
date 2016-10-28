#include "charvariant.h"

#if HEAP_VARIANT

#include "utility.h"

CharVariant::CharVariant(char value)
    : value(value) {
}

VariantPrivate *CharVariant::clone() const {
    return new CharVariant(value);
}

Variant::Type CharVariant::type() const {
    return Variant::Char;
}

int CharVariant::toInteger() const {
    return value;
}

double CharVariant::toReal() const {
    return value;
}

char CharVariant::toChar() const {
    return value;
}

std::string CharVariant::toString() const {
    return Utility::toString(value);
}

#endif

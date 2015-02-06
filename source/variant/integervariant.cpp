#include "integervariant.h"

#include "utility.h"

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

double IntegerVariant::toFloat() const {
    return value;
}

char IntegerVariant::toChar() const {
    return value;
}

string IntegerVariant::toString() const {
    return Utility::toString(value);
}

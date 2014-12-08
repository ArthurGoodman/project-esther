#include "nullvariant.h"

VariantPrivate *NullVariant::clone() const {
    return new NullVariant;
}

Variant::Type NullVariant::type() const {
    return Variant::Null;
}

int NullVariant::toInteger() const {
    return 0;
}

double NullVariant::toFloat() const {
    return 0;
}

char NullVariant::toChar() const {
    return 0;
}

string NullVariant::toString() const {
    return "";
}

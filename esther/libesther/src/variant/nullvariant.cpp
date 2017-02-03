#include "variant/nullvariant.h"

#if HEAP_VARIANT

namespace es {

VariantPrivate *NullVariant::clone() const {
    return new NullVariant;
}

Variant::Type NullVariant::type() const {
    return Variant::Null;
}

int NullVariant::toInteger() const {
    return 0;
}

double NullVariant::toReal() const {
    return 0;
}

char NullVariant::toChar() const {
    return 0;
}

std::string NullVariant::toString() const {
    return "";
}
}

#endif

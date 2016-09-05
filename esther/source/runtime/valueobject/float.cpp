#include "float.h"

Float::Float(double value)
    : ValueObject(value) {
}

Float::Float()
    : ValueObject(0.) {
}

void Float::setValue(double value) {
    setVariant(Variant(value));
}

std::string Float::toString() {
    return value.toString();
}

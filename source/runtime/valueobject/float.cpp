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

bool Float::equals(IObject *other) {
    return dynamic_cast<Float *>(other) && value.toFloat() == ((Float *)other)->value.toFloat();
}

string Float::toString() {
    return value.toString();
}

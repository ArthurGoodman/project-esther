#include "integer.h"

Integer::Integer(int value)
    : ValueObject(value) {
}

Integer::Integer()
    : ValueObject(0) {
}

void Integer::setValue(int value) {
    setVariant(Variant(value));
}

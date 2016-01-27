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

bool Integer::equals(Object *other) {
    return dynamic_cast<Integer *>(other) && value.toInteger() == ((Integer *)other)->value.toInteger();
}

string Integer::toString() {
    return value.toString();
}

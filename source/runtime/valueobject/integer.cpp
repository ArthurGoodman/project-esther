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

bool Integer::immediateEquals(Object *other) {
    return dynamic_cast<Integer *>(other) && value.toInteger() == ((Integer *)other)->value.toInteger();
}

string Integer::immediateToString() {
    return value.toString();
}

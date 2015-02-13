#include "valueobject.h"

namespace esther {

ValueObject::ValueObject(int value)
    : Object("Integer"), value(value) {
}

ValueObject::ValueObject(double value)
    : Object("Float"), value(value) {
}

ValueObject::ValueObject(char value)
    : Object("Char"), value(value) {
}

ValueObject::ValueObject(string value)
    : Object("String"), value(value) {
}

Variant ValueObject::getVariant() {
    return value;
}

string ValueObject::toString() {
    return value.toString();
}
}

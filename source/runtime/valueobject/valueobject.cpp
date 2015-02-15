#include "valueobject.h"

ValueObject::ValueObject(int value)
    : Object("Integer"), value(value) {
}

ValueObject::ValueObject(double value)
    : Object("Float"), value(value) {
}

ValueObject::ValueObject(char value)
    : Object("Character"), value(value) {
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

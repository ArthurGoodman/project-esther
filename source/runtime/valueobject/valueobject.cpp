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

ValueObject::ValueObject(const Variant &value)
    : Object(typeToClassName(value.type())), value(value) {
}

Variant ValueObject::getVariant() {
    return value;
}

string ValueObject::toString() {
    return value.toString();
}

Object *ValueObject::clone() {
    return new ValueObject(value);
}

void ValueObject::setVariant(Variant value) {
    this->value = value;
}

string ValueObject::typeToClassName(Variant::Type type) {
    switch (type) {
    case Variant::Integer:
        return "Integer";
    case Variant::Float:
        return "Float";
    case Variant::Char:
        return "Character";
    case Variant::String:
        return "String";

    default:
        return "";
    }
}

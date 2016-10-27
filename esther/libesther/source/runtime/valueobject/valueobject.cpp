#include "valueobject.h"

#include "integer.h"
#include "float.h"
#include "character.h"
#include "stringvalueobject.h"

ValueObject *ValueObject::createNewInstance(const Variant &value) {
    switch (value.getType()) {
    case Variant::Integer:
        return new Integer(value.toInteger());
    case Variant::Real:
        return new Float(value.toReal());
    case Variant::Char:
        return new Character(value.toChar());
    case Variant::String:
        return new String(value.toString());

    default:
        return 0;
    }
}

ValueObject::ValueObject(int value)
    : Object("Integer"), value(value) {
}

ValueObject::ValueObject(double value)
    : Object("Float"), value(value) {
}

ValueObject::ValueObject(char value)
    : Object("Character"), value(value) {
}

ValueObject::ValueObject(const std::string &value)
    : Object("String"), value(value) {
}

ValueObject::ValueObject(const Variant &value)
    : Object(typeToClassName(value.getType())), value(value) {
}

Variant ValueObject::getVariant() {
    return value;
}

void ValueObject::setVariant(Variant value) {
    this->value = value;
}

std::string ValueObject::typeToClassName(Variant::Type type) {
    switch (type) {
    case Variant::Integer:
        return "Integer";
    case Variant::Real:
        return "Float";
    case Variant::Char:
        return "Character";
    case Variant::String:
        return "String";

    default:
        return "";
    }
}

#include "valueobject.h"

#include "runtime.h"
#include "integerclass.h"
#include "floatclass.h"
#include "characterclass.h"
#include "stringclass.h"

Object *ValueObject::createNewInstance(Runtime *runtime, const Variant &value) {
    switch (value.getType()) {
    case Variant::Integer:
        return runtime->createInteger(value.toInteger());

    case Variant::Real:
        return runtime->createFloat(value.toReal());

    case Variant::Char:
        return runtime->createCharacter(value.toChar());

    case Variant::String:
        return runtime->createString(value.toString());

    default:
        return 0;
    }
}

Variant ValueObject::getVariant() {
    return value;
}

std::string ValueObject::toString() const {
    return value.toString();
}

ValueObject::ValueObject(Class *objectClass, const Variant &value)
    : Object(objectClass), value(value) {
}

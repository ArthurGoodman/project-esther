#include "valueobject.h"

#include "context.h"
#include "runtime.h"
#include "integerclass.h"
#include "floatclass.h"
#include "characterclass.h"
#include "stringclass.h"

Object *ValueObject::createNewInstance(Context *context, const Variant &value) {
    switch (value.getType()) {
    case Variant::Integer:
        return ((IntegerClass *)context->getRuntime()->getRootClass("Integer"))->createInteger(value.toInteger());

    case Variant::Real:
        return ((FloatClass *)context->getRuntime()->getRootClass("Float"))->createFloat(value.toReal());

    case Variant::Char:
        return ((CharacterClass *)context->getRuntime()->getRootClass("Character"))->createCharacter(value.toChar());

    case Variant::String:
        return ((StringClass *)context->getRuntime()->getRootClass("String"))->createString(value.toString());

    default:
        return 0;
    }
}

Variant ValueObject::getVariant() {
    return value;
}

ValueObject::ValueObject(Class *objectClass, const Variant &value)
    : Object(objectClass), value(value) {
}

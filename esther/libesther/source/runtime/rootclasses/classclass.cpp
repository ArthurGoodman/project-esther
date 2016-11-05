#include "classclass.h"

#include "booleanclass.h"
#include "characterclass.h"
#include "floatclass.h"
#include "functionclass.h"
#include "integerclass.h"
#include "nullclass.h"
#include "objectclass.h"
#include "stringclass.h"

ClassClass::ClassClass()
    : Class("Class") {
}

Class *ClassClass::createClass(const std::string &name, Class *superclass) {
    return new Class(this, name, superclass ? superclass : getSuperclass());
}

BooleanClass *ClassClass::createBooleanClass() {
    return new BooleanClass(this);
}

CharacterClass *ClassClass::createCharacterClass() {
    return new CharacterClass(this);
}

FloatClass *ClassClass::createFloatClass() {
    return new FloatClass(this);
}

FunctionClass *ClassClass::createFunctionClass() {
    return new FunctionClass(this);
}

IntegerClass *ClassClass::createIntegerClass() {
    return new IntegerClass(this);
}

NullClass *ClassClass::createNullClass() {
    return new NullClass(this);
}

ObjectClass *ClassClass::createObjectClass() {
    return new ObjectClass(this);
}

StringClass *ClassClass::createStringClass() {
    return new StringClass(this);
}

Object *ClassClass::createNewInstance() {
    return createClass("");
}

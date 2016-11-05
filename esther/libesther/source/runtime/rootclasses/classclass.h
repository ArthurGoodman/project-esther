#pragma once

#include "class.h"

class BooleanClass;
class CharacterClass;
class FloatClass;
class FunctionClass;
class IntegerClass;
class NullClass;
class ObjectClass;
class StringClass;

class ClassClass : public Class {
public:
    ClassClass();

    Class *createClass(const std::string &name, Class *superclass = nullptr);

    BooleanClass *createBooleanClass();
    CharacterClass *createCharacterClass();
    FloatClass *createFloatClass();
    FunctionClass *createFunctionClass();
    IntegerClass *createIntegerClass();
    NullClass *createNullClass();
    ObjectClass *createObjectClass();
    StringClass *createStringClass();

protected:
    Object *createNewInstance();
};

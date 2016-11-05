#pragma once

#include "class.h"

class ValueObject;

class CharacterClass : public Class {
    friend class ClassClass;

public:
    ValueObject *createCharacter(char value);

protected:
    Object *createNewInstance();

private:
    CharacterClass(Class *objectClass);
};
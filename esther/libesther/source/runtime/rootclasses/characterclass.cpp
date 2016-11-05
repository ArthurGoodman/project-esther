#include "characterclass.h"

#include "valueobject.h"

ValueObject *CharacterClass::createCharacter(char value) {
    return new ValueObject(this, value);
}

Object *CharacterClass::createNewInstance() {
    return createCharacter('\0');
}

CharacterClass::CharacterClass(Class *objectClass)
    : Class(objectClass, "Character", objectClass->getSuperclass()) {
}

#include "characterclass.h"

#include "valueobject.h"

ValueObject *CharacterClass::createCharacter(char value) {
    return new ValueObject(this, value);
}

Object *CharacterClass::createNewInstance() {
    return createCharacter('\0');
}

void CharacterClass::setupMethods() {
}

CharacterClass::CharacterClass(Runtime *runtime, Class *objectClass)
    : RootClass(runtime, objectClass, "Character", objectClass->getSuperclass()) {
}

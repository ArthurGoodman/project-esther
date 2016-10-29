#include "characterclass.h"

#include "valueobject.h"

Object *CharacterClass::createCharacter(char value) {
    return new ValueObject(this, value);
}

void CharacterClass::setupMethods() {
}

Object *CharacterClass::createNewInstance() {
    return createCharacter('\0');
}

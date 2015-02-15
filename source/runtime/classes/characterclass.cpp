#include "characterclass.h"

#include "runtime.h"
#include "character.h"

CharacterClass::CharacterClass()
    : RootClass("Character") {
}

Object *CharacterClass::newInstance() {
    return new Character;
}

void CharacterClass::setupMethods() {
}

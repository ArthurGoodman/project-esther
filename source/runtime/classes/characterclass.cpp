#include "characterclass.h"

#include "runtime.h"
#include "character.h"

CharacterClass::CharacterClass()
    : Class("Character") {
    Runtime::setRootClass(this);
}

Object *CharacterClass::newInstance() {
    return new Character;
}

void CharacterClass::setupMethods() {
}

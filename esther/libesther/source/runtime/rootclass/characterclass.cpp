#include "characterclass.h"

#include "valueobject.h"
#include "runtime.h"

ValueObject *CharacterClass::createCharacter(char value) {
    return new ValueObject(this, value);
}

Object *CharacterClass::createNewInstance(const std::vector<Object *> &) {
    return createCharacter('\0');
}

void CharacterClass::setupMethods() {
}

CharacterClass::CharacterClass(Runtime *runtime)
    : RootClass(runtime, "Character", runtime->getObjectClass()) {
}

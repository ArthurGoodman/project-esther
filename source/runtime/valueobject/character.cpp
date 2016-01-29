#include "character.h"

Character::Character(char value)
    : ValueObject(value) {
}

Character::Character()
    : ValueObject('\0') {
}

void Character::setValue(char value) {
    setVariant(Variant(value));
}

bool Character::equals(IObject *other) {
    return dynamic_cast<Character *>(other) && value.toChar() == ((Character *)other)->value.toChar();
}

std::string Character::toString() {
    return value.toString();
}

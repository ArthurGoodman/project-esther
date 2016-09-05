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

std::string Character::toString() {
    return value.toString();
}

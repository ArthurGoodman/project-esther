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

bool Character::immediateEquals(Object *other) {
    return dynamic_cast<Character *>(other) && value.toChar() == ((Character *)other)->value.toChar();
}

string Character::immediateToString() {
    return value.toString();
}

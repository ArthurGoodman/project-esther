#include "character.h"

Character::Character(char value)
    : ValueObject(value) {
}

Character::Character()
    : ValueObject('\0') {
}

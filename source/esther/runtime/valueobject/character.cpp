#include "character.h"

namespace esther {

Character::Character(char value)
    : ValueObject(value) {
}

Character::Character()
    : ValueObject('\0') {
}
}

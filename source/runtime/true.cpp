#include "true.h"

True::True()
    : Object("Boolean") {
}

bool True::isTrue() {
    return true;
}

bool True::isFalse() {
    return false;
}

string True::toString() {
    return "true";
}

Object *True::clone() {
    return this;
}

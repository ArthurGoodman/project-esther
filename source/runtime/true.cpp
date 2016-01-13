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

bool True::isNull() {
    return false;
}

string True::immediateToString() {
    return "true";
}

Object *True::clone() {
    return this;
}

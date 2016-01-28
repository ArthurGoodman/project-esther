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

IObject *True::clone() {
    return this;
}

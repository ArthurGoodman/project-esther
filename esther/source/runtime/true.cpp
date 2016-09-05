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

std::string True::toString() {
    return "true";
}

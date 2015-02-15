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

string True::toString() {
    return "true";
}

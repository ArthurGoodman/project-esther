#include "true.h"

True::True()
    : Object("Boolean") {
}

bool True::isTrue() {
    return true;
}

std::string True::toString() {
    return "true";
}

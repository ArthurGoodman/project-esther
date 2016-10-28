#include "true.h"

bool True::isTrue() {
    return true;
}

std::string True::toString() {
    return "true";
}

True::True(Class *objectClass)
    : Object(objectClass) {
}

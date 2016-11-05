#include "true.h"

std::string True::toString() {
    return "true";
}

True::True(Class *objectClass)
    : Object(objectClass) {
}

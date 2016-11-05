#include "true.h"

std::string True::toString() const {
    return "true";
}

True::True(Class *objectClass)
    : Object(objectClass) {
}

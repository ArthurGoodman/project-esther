#include "null.h"

bool Null::isTrue() {
    return false;
}

std::string Null::toString() {
    return "null";
}

Null::Null(Class *objectClass)
    : Object(objectClass) {
}

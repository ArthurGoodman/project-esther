#include "null.h"

std::string Null::toString() const {
    return "null";
}

bool Null::isTrue() const {
    return false;
}

Null::Null(Class *objectClass)
    : Object(objectClass) {
}

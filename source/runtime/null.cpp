#include "null.h"

Null::Null()
    : Object("Null") {
}

bool Null::isTrue() {
    return false;
}

bool Null::isFalse() {
    return true;
}

std::string Null::toString() {
    return "null";
}

IObject *Null::clone() {
    return this;
}

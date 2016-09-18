#include "null.h"

Null::Null()
    : Object("Null") {
}

bool Null::isTrue() {
    return false;
}

std::string Null::toString() {
    return "null";
}

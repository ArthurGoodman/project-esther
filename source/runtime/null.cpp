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

string Null::toString() {
    return "null";
}

Object *Null::clone() {
    return this;
}

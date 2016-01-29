#include "false.h"

False::False()
    : Object("Boolean") {
}

bool False::isTrue() {
    return false;
}

bool False::isFalse() {
    return true;
}

std::string False::toString() {
    return "false";
}

IObject *False::clone() {
    return this;
}

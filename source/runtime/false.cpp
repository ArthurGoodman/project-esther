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

string False::toString() {
    return "false";
}

Object *False::clone() {
    return this;
}

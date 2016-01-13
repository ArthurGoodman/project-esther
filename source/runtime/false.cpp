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

bool False::isNull() {
    return false;
}

string False::immediateToString() {
    return "false";
}

Object *False::clone() {
    return this;
}

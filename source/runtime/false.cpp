#include "false.h"

False::False()
    : Object("FalseClass") {
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

string False::toString() {
    return "false";
}

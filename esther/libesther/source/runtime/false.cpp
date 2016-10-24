#include "false.h"

False::False()
    : Object("Boolean") {
}

bool False::isTrue() {
    return false;
}

std::string False::toString() {
    return "false";
}

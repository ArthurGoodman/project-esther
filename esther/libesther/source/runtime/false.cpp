#include "false.h"

bool False::isTrue() {
    return false;
}

std::string False::toString() {
    return "false";
}

False::False(Class *objectClass)
    : Object(objectClass) {
}

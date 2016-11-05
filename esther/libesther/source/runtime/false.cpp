#include "false.h"

std::string False::toString() const {
    return "false";
}

bool False::isTrue() const {
    return false;
}

False::False(Class *objectClass)
    : Object(objectClass) {
}

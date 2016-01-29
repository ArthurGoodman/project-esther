#include "outofrangeexception.h"

std::string OutOfRangeException::message() {
    return "index out of range";
}

void OutOfRangeException::raise() {
    throw this;
}

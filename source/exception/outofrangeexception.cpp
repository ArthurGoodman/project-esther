#include "outofrangeexception.h"

string OutOfRangeException::message() {
    return "index out of range";
}

void OutOfRangeException::raise() {
    throw this;
}

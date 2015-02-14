#include "errorexception.h"

namespace esther {

ErrorException::ErrorException(string message, Position pos)
    : Exception(message), position(pos) {
}

Position ErrorException::pos() {
    return position;
}
}

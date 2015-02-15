#include "errorexception.h"

ErrorException::ErrorException(string message, Position position)
    : msg(message), pos(position) {
}

string ErrorException::message() {
    return msg;
}

Position ErrorException::position() {
    return pos;
}
